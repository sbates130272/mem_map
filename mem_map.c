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
#include <asm/pgtable.h>

static void prettyprint_struct_page(unsigned long pfn, struct page *in)
{
    printk(KERN_INFO "Hello, this is prettyprint_struct_page() for pfn %lx.\n",
        pfn);
    printk(KERN_INFO "in->flags = %lx.\n\n", in->flags);
}

static int __init init_mem_map(void)
{
    unsigned long mypfn = 0;
    struct page *mypage;
    int node;

    printk(KERN_INFO "Hello, this is init_mem_map().\n");
    printk(KERN_INFO "You have %lu pages to play with!\n",
           get_num_physpages());

    for (node = 0 ; node < MAX_NUMNODES ; node++)
        printk(KERN_INFO "node_data[%d]->node_start_pfn = %lu.\n",
               node, node_data[node]->node_start_pfn);

    mypage = pfn_to_page(node_data[0]->node_start_pfn);
    prettyprint_struct_page(mypfn, mypage);

    return 0;
}

static void __exit exit_mem_map(void)
{
    printk(KERN_INFO "Goodbye, this is exit_mem_map().\n");
}

module_init(init_mem_map);
module_exit(exit_mem_map);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephen Bates <stephen.bates@pmcs.com>");
MODULE_DESCRIPTION("Displays information on system memory in /proc/mem_map");
