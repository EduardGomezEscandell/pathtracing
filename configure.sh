export CC="clang"
export CXX="clang++"

export PROJECT_DIR="$(pwd -P)"

export BUILD_TYPE=${BUILD_TYPE:-Release}
echo "Build type: ${BUILD_TYPE}"

export BUILD_DIR="${PROJECT_DIR}/build"
export BIN_DIR="${PROJECT_DIR}/bin/${BUILD_TYPE}"
export SOURCE_DIR="${PROJECT_DIR}"

# Building
cmake                                               \
-B"${BUILD_DIR}/${BUILD_TYPE}" -H"${SOURCE_DIR}"    \
-DCMAKE_BUILD_TYPE=${BUILD_TYPE}

cmake --build "${BUILD_DIR}/${BUILD_TYPE}" -- -j$(nproc)

# Creating links in bin
rm -rf "${BIN_DIR}"
mkdir "${BIN_DIR}"
ln -s "${BUILD_DIR}/${BUILD_TYPE}/test/${BUILD_TYPE}/run_tests.exe" "${BIN_DIR}/run_tests.exe"
ln -s "${BUILD_DIR}/${BUILD_TYPE}/src/${BUILD_TYPE}/pathtracer.exe" "${BIN_DIR}/pathtracer.exe"

# Compile commands
ln -sf "${BUILD_DIR}/${BUILD_TYPE}/compile_commands.json" "${PROJECT_DIR}/compile_commands.json"