#ifndef SHADERDESCRIPTION_H
#define SHADERDESCRIPTION_H
#include <filesystem>
namespace mini {
enum class ShaderStage {
    Vertex,
    Fragment,
    Geometry,
    TessControl,
    TessEval,
    Compute
};
struct ShaderDescription {
    ShaderStage stage;
    std::filesystem::path shaderPath;
};
}
#endif // SHADERDESCRIPTION_H
