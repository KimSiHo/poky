DESCRIPTION = "Simple hellowrold application example"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=d41d8cd98f00b204e9800998ecf8427e"

inherit systemd

FILESEXTRAPATHS:prepend := "${THISDIR}/source:"
S = "${WORKDIR}"

SRC_URI += "file://hello.c"
SRC_URI += "file://COPYING"
SRC_URI += "file://hello.service"

SYSTEMD_SERVICE:${PN} = "hello.service"
SYSTEMD_AUTO_ENABLE = "enable"

do_compile() {
	${CC} hello.c ${LDFLAGS} -o hello
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 hello ${D}${bindir}

	install -d ${D}${systemd_unitdir}/system
	install -m 0644 hello.service ${D}${systemd_unitdir}/system
}

FILES:${PN} += "${bindir}/hello"
FILES:${PN} += "${systemd_unitdir}/system/hello.service"
