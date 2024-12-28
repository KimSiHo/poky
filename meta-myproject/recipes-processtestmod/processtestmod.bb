SUMMARY = "Linux Kernel process test module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=f30c070c6fdae214248d064e918c1182"

S = "${WORKDIR}"

inherit module

FILESEXTRAPATHS:prepend := "${THISDIR}/file:"
SRC_URI = "\
    file://Makefile \
    file://main.c \
    file://COPYING \
"

KERNEL_MODULE_AUTOLOAD += "processtestmod"

ALLOW_EMPTY:${PN} = "1"
