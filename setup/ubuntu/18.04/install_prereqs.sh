#!/bin/bash
set -euo pipefail

if [[ "${EUID}" -ne 0 ]]; then
  echo 'This script must be run as root' >&2
  exit 1
fi
apt-get update
apt-get install -y software-properties-common
add-apt-repository ppa:dreal/dreal -y  # For libibex-dev
apt-get update
apt-get install -y --no-install-recommends $(tr '\n' ' ' <<EOF
bison
coinor-libclp-dev
g++
g++-5
libfl-dev
libibex-dev
libnlopt-dev
libpython2.7-dev
pkg-config
python-dev
zlib1g-dev
EOF
)
      
# Install bazel
BAZEL_VERSION=0.21.0
BAZEL_DEBNAME=bazel_${BAZEL_VERSION}-linux-x86_64.deb
BAZEL_URL=https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/${BAZEL_DEBNAME}
BAZEL_SHA256=cdc225dd1c1eb52ac7f4b0bebb40d2c6d6d8bc0f273718b26281077cd70a0403
apt-get install -y --no-install-recommends wget
wget ${BAZEL_URL}
if echo "${BAZEL_SHA256}  ${BAZEL_DEBNAME}" | sha256sum -c; then
    apt-get install -y ./${BAZEL_DEBNAME}
    rm ${BAZEL_DEBNAME}
else
    echo "SHA256 does not match ${BAZEL_DEBNAME}:"
    echo "    expected: ${BAZEL_SHA256}"
    echo "    actual  : `sha256sum ${BAZEL_DEBNAME}`"
    exit 1
fi
