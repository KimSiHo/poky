SUMMARY = "Linux Kernel data structure test module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=ab7f28a4ed1fab21c00f77e90ac182cd"

S = "${WORKDIR}"

inherit module

FILESEXTRAPATHS:prepend := "${THISDIR}/file:"
SRC_URI = "\
    file://Makefile \
    file://COPYING \
    file://sysfs-class.c \
"

KERNEL_MODULE_AUTOLOAD += "sysfs-class"

ALLOW_EMPTY:${PN} = "1"
