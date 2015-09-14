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

static int __init init_mem_map(void)
{
    printk(KERN_INFO "Hello, this is init_mem_map().\n");
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
