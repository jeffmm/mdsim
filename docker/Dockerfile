FROM jeffmm/python-cpp-ml
COPY ./requirements.txt /build/requirements.txt
WORKDIR /build
RUN pip install -r requirements.txt
WORKDIR /mnt
RUN rm -rf /build
