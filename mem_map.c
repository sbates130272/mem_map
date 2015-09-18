//////////////////////////////////////////////////////////////////////
//                             PMC-Sierra, Inc.
//
//
//
//                             Copyright 2015
//
////////////////////////////////////////////////////////////////////////
//
// This program is free software; you can redistribute it and/or modify it
// under the terms and conditions of the GNU General Public License,
// version 2, as published by the Free Software Foundation.
//
// This program is distributed in the hope it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
//
////////////////////////////////////////////////////////////////////////
//
//   Author:  Stephen Bates
//
//   Description:
//     Loadable Kernel Module for looking at system memory.
//
////////////////////////////////////////////////////////////////////////

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/debugfs.h>
#include <asm/pgtable.h>

#define MODULENAME "mem_map"
#define NUMPAGES 16

static struct dentry *debugfs;

static void prettyprint_struct_page(unsigned long pfn, struct page *page)
{
    printk(KERN_INFO "Hello, this is prettyprint_struct_page() for pfn %lx.\n",
        pfn);
    printk(KERN_INFO "page->flags     = %lx.\n", page->flags);
    printk(KERN_INFO "page->_mapcount = %d.\n", atomic_read(&page->_mapcount));
    printk(KERN_INFO "page->_count    = %d.\n", atomic_read(&page->_count));
}

static int write_pfn(void *data, u64 pfn)
{
    struct page *page;

    printk(KERN_INFO "Hello, this is write_pfn() for pfn %lx.\n",
           (unsigned long)pfn);
    page = pfn_to_page((unsigned long)pfn);
    prettyprint_struct_page(pfn, page);

    return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(pfn_fops, NULL, write_pfn, "%llu\n");

static int __init init_mem_map(void)
{
    struct page *mypage;
    int pfn, nid, nodes = 0;

    debugfs = debugfs_create_dir(MODULENAME, NULL);
    if (debugfs == NULL )
        printk(KERN_INFO "Unable to create debugfs directory.");
    if (debugfs_create_file("pfn", 0222, debugfs, NULL, &pfn_fops) == NULL)
        printk(KERN_INFO "Unable to create debugfs file pfn.");

    printk(KERN_INFO "\n\n********************************************\n");
    printk(KERN_INFO "Hello, this is init_mem_map().\n");
    printk(KERN_INFO "You have %lu pages to play with!\n",
           get_num_physpages());

    for_each_online_node(nid){
	    nodes++;
	    printk(KERN_INFO "node_data[%d]->node_start_pfn = %lu.\n",
		   nid, node_data[nid]->node_start_pfn);
	    printk(KERN_INFO "node_data[%d]->node_present_pages = %lu.\n",
		   nid, node_data[nid]->node_present_pages);
	    printk(KERN_INFO "node_data[%d]->node_spanned_pages = %lu.\n",
		   nid, node_data[nid]->node_spanned_pages);
    }
    printk(KERN_INFO "You have %d node(s) to play with!\n",
           nodes);

    for (pfn=0; pfn < NUMPAGES ; pfn++){
	    mypage = pfn_to_page(node_data[0]->node_start_pfn+pfn);
	    prettyprint_struct_page(node_data[0]->node_start_pfn+pfn,
				    mypage);
    }

    return 0;
}

static void __exit exit_mem_map(void)
{
    printk(KERN_INFO "Goodbye, this is exit_mem_map().\n");
    debugfs_remove_recursive(debugfs);
}

module_init(init_mem_map);
module_exit(exit_mem_map);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephen Bates <stephen.bates@pmcs.com>");
MODULE_DESCRIPTION("Displays information on system memory.");
