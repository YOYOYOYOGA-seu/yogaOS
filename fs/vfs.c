/*
 * @Author Shi Zhangkun
 * @Date 2020-12-06 13:53:01
 * @LastEditTime 2020-12-28 09:36:12
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/fs/vfs.c
 */

#include "vfs.h"
#include "mount.h"
#include "yogaOS/list.h"
#include "yogaOS/types.h"
#include "string.h"
#include "errno.h"
static miniList_t(fsType_t) fs_list = {0, NULL};


fsType_t* vfs_findFS(const char* name)
{
  fsType_t* p = fs_list.firstItem;
  for(size_t i = 0; i < fs_list.value && p != NULL; i++)
  {
    if(strcmp(p->name,name) == 0)
      return p;
    else
      p = p->fs_list.pNext;
  }
  return NULL;
}

error_t vfs_registerFS(const fsType_t* fs)
{
  if(vfs_findFS(fs->name) != NULL)
  {
    list_insertTail(&fs_list, &fs->fs_list);
    return ENOERR;
  }
  return ENOENT;
}
