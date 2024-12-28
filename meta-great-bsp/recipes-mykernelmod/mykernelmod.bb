SUMMARY = "Example of how to build an external linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=4521f6ed8a0f537c34c06d40a4716ec4"

S = "${WORKDIR}"
RPROVIDES:${PN} += "kernel-module-mykernelmod"

inherit module

FILESEXTRAPATHS:prepend := "${THISDIR}/file:"
SRC_URI = "\
    file://Makefile \
    file://mykernelmod.c \
    file://COPYING \
"

KERNEL_MODULE_AUTOLOAD += "mykernelmod"

ALLOW_EMPTY:${PN} = "1"
