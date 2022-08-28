FROM almalinux:9

RUN dnf update -y
RUN dnf group install -y "Development Tools"
RUN dnf group info "Development Tools"
RUN dnf --enablerepo=crb install ninja-build -y
RUN dnf install -y cmake
RUN dnf clean all -y
RUN dnf install -y python3-pip
RUN pip install conan --pre

ADD profiles /root/.conan2/profiles

CMD ["bash"]