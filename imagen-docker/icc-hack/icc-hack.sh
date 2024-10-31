#!/bin/bash

error() {
    echo "$@"
    exit 1
}

disable() {
    if [[ -L /usr/include ]] ; then
        rm /usr/include
    else
        error "/usr/include no es un enlace"
    fi
    ln -s /usr/include.original /usr/include
}

enable() {
    if [[ -L /usr/include ]] ; then
        rm /usr/include
    else
        error "/usr/include no es un enlace"
    fi
    ln -s "${SCRIPT_DIR}/usr/include" /usr/include 
}

update_includes() (
    cd /usr/include.original
    for i in * ; do
        if [[ ! -e "${SCRIPT_DIR}/usr/include/$i" ]] ; then
            ln -s "$(realpath "$i")" "${SCRIPT_DIR}/usr/include"
        fi
    done
)

setup() {
    if [[ -L /usr/include ]] ; then
        error "/usr/include ya es un enlace"
    fi
    mv /usr/include /usr/include.original
    ln -s /usr/include.original /usr/include

    tar xf "${SCRIPT_DIR}/includes.tar.xz" -C "${SCRIPT_DIR}/"
    rm "${SCRIPT_DIR}/includes.tar.xz"

    for i in icpc icc \
                  codecov map_opts mcpcom profdcg profmerge \
                  profmergesampling proforder tselect xiar xild \
             ; do
        D="$(dirname "$(which "$i")")" # /opt/intel/oneapi/compiler/2023.2.1/linux/bin/intel64
        mv "$D/$i" "$D/$i.original"
        ln -s "$SCRIPT_DIR/wrap" "$D/$i"
    done
    update_includes
}

enabled() {
    [[ "$(realpath /usr/include)" = "${SCRIPT_DIR}/usr/include" ]]
}
