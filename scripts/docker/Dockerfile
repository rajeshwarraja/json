FROM almalinux:9

RUN dnf update -y
RUN dnf group install -y "Development Tools"
RUN dnf --enablerepo=crb install -y ninja-build
RUN dnf install -y cmake
RUN dnf install -y python3-pip
RUN dnf clean all -y
RUN pip install conan --pre

RUN conan profile detect

ADD profiles /root/.conan2/profiles

LABEL version="1.0"

CMD ["bash"]