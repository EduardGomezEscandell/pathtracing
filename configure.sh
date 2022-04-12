clear

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
mkdir -p "${BIN_DIR}"
ln -s "${BUILD_DIR}/${BUILD_TYPE}/test/run_tests" "${BIN_DIR}/run_tests"
ln -s "${BUILD_DIR}/${BUILD_TYPE}/src/pathtracer" "${BIN_DIR}/pathtracer"

chmod +x "${BIN_DIR}/run_tests"
chmod +x "${BIN_DIR}/pathtracer"

# Compile commands
ln -sf "${BUILD_DIR}/${BUILD_TYPE}/compile_commands.json" "${PROJECT_DIR}/compile_commands.json"