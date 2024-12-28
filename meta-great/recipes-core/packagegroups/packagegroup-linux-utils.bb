DESCRIPTION = "utils package provided by provided layers"

inherit packagegroup

PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS:${PN} = "\
    vim \
    procps \
"
