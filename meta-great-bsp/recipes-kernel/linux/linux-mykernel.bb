DESCRIPTION = "Linux kernel from kernel.org git repositoy"
SECTION = "kernel"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

inherit kernel
inherit kernel-yocto
inherit externalsrc

EXTERNALSRC = "/home/sihokim/projects/linux"
KBUILD_DEFCONFIG = "custom_generic_defconfig"

LINUX_VERSION ?= "5.4.0-1"
LINUX_VERSION_EXTENSION  = "-generic"

PROVIDES += "virtual/kernel"

PV = "${LINUX_VERSION}"
COMPATIBLE_MACHINE = "great"

KCONFIG_MODE = "alldefconfig"
