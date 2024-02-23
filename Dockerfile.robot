FROM nvcr.io/nvidia/l4t-pytorch:r35.1.0-pth1.12-py3

RUN apt-get update
RUN apt-get install -y vim git
RUN DEBIAN_FRONTEND=oninteractive apt-get install -y wget unzip
RUN python3 -m pip install --upgrade pip

RUN DEBIAN_FRONTEND=oninteractive apt-get install -y make bash  git gcc-8 g++-8 autoconf libtool automake build-essential \
                   libncurses-dev zlib1g-dev binutils-dev libgl1-mesa-dev \
                   libvdpau-dev libegl1-mesa-dev libssl-dev rpcbind \
                   texinfo bison flex python3 libibverbs-dev \
                   libasan5 cppcheck wget libexpat1 xz-utils libglu1-mesa-dev freeglut3-dev rpm2cpio \
                   cpio liblzma-dev libexpat1-dev libelf-dev libfreeimage3 libfreeimage-dev systemd
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 100
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 100

# rebuild pytorch
RUN pip uninstall -y torch
RUN apt-get install -y ca-certificates ccache curl libjpeg-dev libpng-dev
WORKDIR /opt
RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.0/cmake-3.28.0.tar.gz
RUN tar xf cmake-3.28.0.tar.gz && rm -f cmake-3.28.0.tar.gz
RUN cd ./cmake-3.28.0 && ./configure && make -j 32 && make install

RUN git config --global core.compression 9
RUN cd /opt && git clone https://github.com/pytorch/pytorch.git
WORKDIR /opt/pytorch
RUN git checkout v1.12.0 && git submodule update --init --recursive
COPY CMakeLists.txt ./aten/src/ATen/
COPY common.mk ./third_party/nccl/nccl/makefiles/
COPY Makefile ./third_party/nccl/nccl/src/
ARG PYTHON_VERSION=3.7
RUN curl -fsSL -v -o ~/miniconda.sh -O  https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-aarch64.sh  && \
    chmod +x ~/miniconda.sh && \
    ~/miniconda.sh -b -p /opt/conda && \
    rm ~/miniconda.sh && \
    /opt/conda/bin/conda install -y python=${PYTHON_VERSION} conda-build pyyaml numpy ipython && \
    /opt/conda/bin/conda clean -ya
ENV PATH /opt/conda/bin:$PATH
RUN conda install numpy pyyaml setuptools cmake cffi typing
RUN pip install typing-extensions
ENV MAX_JOBS=6
ENV CMAKE_PREFIX_PATH="$(dirname $(which conda))/../"
ENV TORCH_CUDA_ARCH_LIST="6.0 6.1 7.0 8.0" 
ENV TORCH_NVCC_FLAGS="-Xfatbin -compress-all -cudart shared"
RUN python setup.py install

WORKDIR /workspace