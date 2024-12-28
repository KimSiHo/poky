SUMMARY = "A very small image for yocto test"

inherit great-base-image

## basic settings
LINGUAS_KO_KR = "ko-kr"
LINGUAS_EN_US = "en-us"
IMAGE_LINGUAS = "${LINGUAS_KO_KR} ${LINGUAS_EN_US}"

IMAGE_OVERHEAD_FACTOR = "1.3"

# https://docs.yoctoproject.org/dunfell/ref-manual/ref-features.html#ref-features-image
IMAGE_FEATURES += "splash package-management ssh-server-openssh tools-sdk debug-tweaks"

IMAGE_INSTALL += "packagegroup-linux-utils"


## extra users
inherit extrausers

EXTRA_USERS_PARAMS = "\
    groupadd greatgroup; \
    useradd -s /bin/bash -g greatgroup -p '' great; \
"


## postprocess command
# 쉘 환경 설정 파일 추가
add_shell_setting_files() {
    mkdir -p ${IMAGE_ROOTFS}/home/great
    mkdir -p ${IMAGE_ROOTFS}/home/root

    echo 'export JAVA_HOME=/usr/lib/jvm/openjdk-8' >> ${IMAGE_ROOTFS}/home/great/.bashrc
    echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ${IMAGE_ROOTFS}/home/great/.bashrc
    echo "alias ls='ls --color=auto'" >> ${IMAGE_ROOTFS}/home/great/.bashrc

    echo "source /home/great/.bashrc" >> ${IMAGE_ROOTFS}/home/great/.bash_profile

    echo 'export JAVA_HOME=/usr/lib/jvm/openjdk-8' >> ${IMAGE_ROOTFS}/home/root/.bashrc
    echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ${IMAGE_ROOTFS}/home/root/.bashrc
    echo "alias ls='ls --color=auto'" >> ${IMAGE_ROOTFS}/home/root/.bashrc

    echo "source /home/root/.bashrc" >> ${IMAGE_ROOTFS}/home/root/.bash_profile
}

# 명령어 추가
add_commands() {
    # Check if symbolic links exist and create symbolic links if they do not
    [ ! -L ${IMAGE_ROOTFS}/bin/lsmod ] && ln -s /bin/kmod ${IMAGE_ROOTFS}/bin/lsmod
    [ ! -L ${IMAGE_ROOTFS}/bin/insmod ] && ln -s /bin/kmod ${IMAGE_ROOTFS}/bin/insmod
    [ ! -L ${IMAGE_ROOTFS}/bin/rmmod ] && ln -s /bin/kmod ${IMAGE_ROOTFS}/bin/rmmod
    [ ! -L ${IMAGE_ROOTFS}/bin/modinfo ] && ln -s /bin/kmod ${IMAGE_ROOTFS}/bin/modinfo
    [ ! -L ${IMAGE_ROOTFS}/bin/modprobe ] && ln -s /bin/kmod ${IMAGE_ROOTFS}/bin/modprobe
    [ ! -L ${IMAGE_ROOTFS}/bin/depmode ] && ln -s /bin/kmod ${IMAGE_ROOTFS}/bin/depmode
}

# 기타 설정 파일 수정
update_setting_files() {
  # FIXME 로컬 환경의 sed에 의존하는데, 이 부분을 다른 방식으로 수정.
  sed -i 's#/bin/sh#/bin/bash#g' ${IMAGE_ROOTFS}/etc/passwd
  sed -i '/^SYSLOG_SU_ENAB/d' ${IMAGE_ROOTFS}/etc/login.defs
  sed -i '/^SYSLOG_SG_ENAB/d' ${IMAGE_ROOTFS}/etc/login.defs
}

ROOTFS_POSTPROCESS_COMMAND += "add_shell_setting_files;add_commands;update_setting_files;"
