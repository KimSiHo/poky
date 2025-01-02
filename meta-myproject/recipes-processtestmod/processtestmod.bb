SUMMARY = "Linux Kernel process test module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=f30c070c6fdae214248d064e918c1182"

S = "${WORKDIR}"

inherit module

FILESEXTRAPATHS:prepend := "${THISDIR}/file:"
SRC_URI = "\
    file://Makefile \
    file://main.c \
    file://gdb-debug.c \
    file://wait-queue.c \
    file://COPYING \
"

# KERNEL_MODULE_AUTOLOAD += "processtestmod"  # wait-queue 테스트로 인한 비활성화

ALLOW_EMPTY:${PN} = "1"
