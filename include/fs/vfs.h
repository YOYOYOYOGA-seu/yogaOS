/*
 * @Author Shi Zhangkun
 * @Date 2020-12-06 13:53:37
 * @LastEditTime 2022-04-14 20:46:03
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/fs/vfs.h
 */
#ifndef __VFS_H
#define __VFS_H

#include "yogaOS/types.h"
#include "yogaOS/list.h"
#include "unistd.h"
#include "time.h"
#include "mount.h"
#include "fs/fcache.h"

#define VFS_SNMAE_SIZE 16

struct vfsmount;
struct inode;
struct fileOperations;
struct dentryOperations;
struct inodeOperations;
struct superOperations;
struct superBlock;

typedef struct superBlock superBlock_t;
#define F_RD      0x01
#define F_WR      0x02
#define F_RDWR    F_RDONLY|F_WRONLY

typedef unsigned int mode_t;
typedef struct fsType fsType_t;
typedef struct inode inode_t;
typedef struct dentry dentry_t;
typedef struct file file_t;
typedef struct nameidata nameidata_t;
typedef struct {
  char* str;
  uint16_t count;
}string_t;

typedef struct{
  uint8_t ifShort;
  union {
    string_t lname;
    char sname[VFS_SNMAE_SIZE];
  };
}dentryName_t;

/**
 * fsType
 */
struct fsType{
  listItem_t fs_list;
  const char* name;
  superBlock_t* (*get_sb)(struct fsType* ,int ,const char*, void*, vfsmount_t*);
  superBlock_t* (*kill_sb)(superBlock_t*);
  list_t supers;
};

/**
 * dentry
 */
struct dentry{
  struct inode* inode;
  struct dentry* parent;
  list_t childList;
  uint16_t count;
  uint16_t flags;
  dentryName_t name;
  struct dentryOperations* op; /* opreation of dentry */
  listItem_t d_list;
};

/**
 * inode
 */
struct inode{
  uint16_t mode;  /* file type and access permission */
  uint16_t uid;  /* owner user id */
  uint16_t gid;
  uint16_t linkNum;
  uint32_t size;  /* file size: bytes */
  uint32_t time;  /* change time */
  

  uint16_t dev;
  uint16_t i_ino;  /* inode number (can find it in inode map)*/
  uint16_t count; /* reference counts */
  uint16_t blockSize;
  uint16_t dataBlockNum;
  vfsBlockHead_t data[7]; /*data block descs */
  vfsBlockHead_t firstOrderMap;  /* desc to block that store data block mapping */
  vfsBlockHead_t secondOrderMap;  /* desc to block that store data block mapping */
  
  uint8_t lock;
  uint8_t dirt;
  uint8_t pipe;
  uint8_t mount;

  
  struct inodeOperations* op; /* opreation of inode */
  listItem_t i_list;
  listItem_t i_dirtList;
};

/**
 * superBlock
 */
struct superBlock{
  uint32_t blockSize; /* one block size */
  uint32_t inodeNum;
  uint32_t BlockNum;  /*total blocks number */
  uint16_t imapBlocks; /*inode map blocks number */
  uint16_t dmapBlocks; /*data map blocks number */
  uint32_t firstDataBlock;
  uint32_t maxFileSize;
  uint32_t magic;

  struct superOperations* op;  /* opreation of superBlock */
  fsType_t* fsType;
  
  uint8_t dirt;
  vfsBlockHead_t *inodeMap;
  vfsBlockHead_t *dataMap;
  vfsBlockHead_t *inodesArea;

  listItem_t s_list;

  list_t s_inodes;
  list_t s_dirt;
};

/**
 * file description
 */
struct file{
  dentry_t* dentry;
  struct fileOperations* op; 
  unsigned int flags;
  mode_t mode;
  listItem_t f_list;
};

/**
 * used for path lookup
 */
 struct nameidata{
  dentry_t dentry;
};



struct dentryOperations{
  int (*d_hash)(dentry_t*, dentryName_t*);
  int (*d_compare)(dentry_t*, dentryName_t*, dentryName_t*);
  int (*d_delete)(dentry_t*);
  void (*d_release)(dentry_t*);
  void (*d_iput)(dentry_t*, inode_t*);
  char* (*d_dname)(dentry_t*, char* , int);

};

struct inodeOperations{
  int (*create)(inode_t*, dentry_t*, int ,nameidata_t*) ;
  int (*link)(dentry_t*, inode_t* , dentry_t *);
  int (*unlink)(inode_t*, dentry_t*);
  int (*mkdir)(inode_t*, dentry_t*, int);
  int (*rmdir)(inode_t*, dentry_t*);
  int (*rename) (inode_t *, dentry_t *, inode_t *, dentry_t *);
};

struct superOperations{
  inode_t *(*alloc_inode)(superBlock_t* );
  void (*destroy_inode)(inode_t* );
  void (*read_inode)(inode_t* );
  void (*dirty_inode)(inode_t* );
  int (*write_inode)(inode_t* ,int);
  void (*clear_inode)(inode_t* );
  void (*delete_inode)(inode_t* );
  void (*write_super)(superBlock_t* );
  void (*sync_fs)(superBlock_t*, int );
};

struct fileOperations{
  int (*open)(inode_t*, file_t*);
  ssize_t (*read)(file_t* , char*, size_t, loff_t*);
  ssize_t (*write)(file_t* , const char*, size_t, loff_t*);
  int (*release)(inode_t*, file_t*);
  int (*fsync)(file_t *, dentry_t*, int);
  int (*llseak)(file_t*, loff_t, int);
};


/* --------------------------- function definition --------------------- */
superBlock_t* superAlloc();
void superFree(superBlock_t* ptr);
#endif