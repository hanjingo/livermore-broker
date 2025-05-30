# livermore-broker

[TOC]



## Dependes

You can use one of the following ways to fetch project dependencies before build this project:

### Use Vcpkg

```sh
cmake -DCMAKE_TOOLCHAIN_FILE=xxx_vcpkg_root_path/scripts/buildsystems/vcpkg.cmake .. #(must be absolute path)
```

or

```sh
vcpkg install --x-install-root=xxx_install_path #(must be absolute path)
# for example: vcpkg install --x-install-root=C:\\work\\livermore-broker\\deps
```

### Use Cmake Internal Tool

```shell
cd build && cmake -DBUILD_DEPS=ON ..
```

