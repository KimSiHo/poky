SUMMARY = "Linux Kernel data structure test module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=ab7f28a4ed1fab21c00f77e90ac182cd"

S = "${WORKDIR}"

inherit module

FILESEXTRAPATHS:prepend := "${THISDIR}/file:"
SRC_URI = "\
    file://Makefile \
    file://main.c \
    file://double-linked-list.c \
    file://single-linked-list.c \
    file://queue.c \
    file://idr.c \
    file://rbtree.c \
    file://COPYING \
"

KERNEL_MODULE_AUTOLOAD += "datastructuretestmod"

ALLOW_EMPTY:${PN} = "1"
