# livermore-broker

[TOC]



## Dependes

You can use one of the following ways to fetch project dependencies before build this project:

### Use vcpkg

```sh
vcpkg install --x-install-root=xxx_install_path #(must be absolute path)
# for example: vcpkg install --x-install-root=C:\\work\\livermore-broker\\deps
vcpkg install
```

### Use Cmake

```shell
cd build && cmake -DBUILD_DEPS=ON ..
```

