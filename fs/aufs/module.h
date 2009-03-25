/*
 * Copyright (C) 2005-2009 Junjiro R. Okajima
 *
 * This program, aufs is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

/*
 * module initialization and module-global
 */

#ifndef __AUFS_MODULE_H__
#define __AUFS_MODULE_H__

#ifdef __KERNEL__

#include <linux/slab.h>

/* module parameters */
extern short aufs_nwkq;
extern int sysaufs_brs;

/* ---------------------------------------------------------------------- */

extern int au_dir_roflags;

void *au_kzrealloc(void *p, unsigned int nused, unsigned int new_sz, gfp_t gfp);
int au_seq_path(struct seq_file *seq, struct path *path);

/* ---------------------------------------------------------------------- */

/* kmem cache */
enum {
	AuCache_DINFO,
	AuCache_ICNTNR,
	AuCache_FINFO,
	AuCache_VDIR,
	AuCache_DEHSTR,
#ifdef CONFIG_AUFS_HINOTIFY
	AuCache_HINOTIFY,
#endif
	AuCache_Last
};

#define AuCache(type)	KMEM_CACHE(type, SLAB_RECLAIM_ACCOUNT)

extern struct kmem_cache *au_cachep[];

#define AuCacheFuncs(name, index) \
static inline void *au_cache_alloc_##name(void) \
{ return kmem_cache_alloc(au_cachep[AuCache_##index], GFP_NOFS); } \
static inline void au_cache_free_##name(void *p) \
{ kmem_cache_free(au_cachep[AuCache_##index], p); }

AuCacheFuncs(dinfo, DINFO);
AuCacheFuncs(icntnr, ICNTNR);
AuCacheFuncs(finfo, FINFO);
AuCacheFuncs(vdir, VDIR);
AuCacheFuncs(dehstr, DEHSTR);

/*  ---------------------------------------------------------------------- */

#endif /* __KERNEL__ */
#endif /* __AUFS_MODULE_H__ */
