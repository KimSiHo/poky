DESCRIPTION = "kernel develop utility files"
LICENSE = "CLOSED"

SRC_URI += "file://set_ftrace.sh"
SRC_URI += "file://get_ftrace.sh"
SRC_URI += "file://process/"


S = "${WORKDIR}"

do_install() {
	install -d ${D}/home/great/scripts
	install -m 0755 set_ftrace.sh ${D}/home/great/scripts
	install -m 0755 get_ftrace.sh ${D}/home/great/scripts

	install -d ${D}/home/great/scripts/process
	install -m 0755 process/create/create.c ${D}/home/great/scripts/process/create
	install -m 0755 process/create/Makefile ${D}/home/great/scripts/process/create
	install -m 0755 process/create/set_ftrace.sh ${D}/home/great/scripts/process/create
}

FILES:${PN} += "/home/great/scripts/*"

INSANE_SKIP:${PN} += "file-rdeps"
