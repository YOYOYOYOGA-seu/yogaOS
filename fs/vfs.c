/*
 * @Author Shi Zhangkun
 * @Date 2020-12-06 13:53:01
 * @LastEditTime 2022-04-14 21:29:36
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/fs/vfs.c
 */

#include "fs/vfs.h"
#include "fs/mount.h"
#include "yogaOS/list.h"
#include "yogaOS/types.h"
#include "string.h"
#include "errno.h"
static list_t fs_list;

void vfs_init(void)
{
  list_initList(&fs_list, 0xFFFFFFFF);
}

fsType_t* vfs_findFS(const char* name)
{
  listItem_t* p = fs_list.pFirstItem;
  for(size_t i = 0; i < fs_list.size && p != NULL; i++)
  {
    if(strcmp(((fsType_t*)p->pOwner)->name, name) == 0)
      return p->pOwner;
    else
      p = p->pNext;
  }
  return NULL;
}

error_t vfs_registerFS(fsType_t* fs)
{
  if(vfs_findFS(fs->name) != NULL)
  {
    list_insertTail(&fs_list, &fs->fs_list);
    return ENOERR;
  }
  return ENOENT;
}
