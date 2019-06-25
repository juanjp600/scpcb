#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <Shader/Shader.h>
#include <Misc/String.h>
#include <map>
#include "Graphics.h"

class Shader {
private:
    static std::map<PGE::Shader*, int> cpyTracker;
    // Increments the copy tracker.
    void increment() const;
    // Decrements the copy tracker and returns true if it tracks no more copies of an object.
    bool decrement() const;

    PGE::Shader* internal = nullptr;

public:
    Shader()=default;

    Shader(const Shader& cpy);
    Shader& operator=(const Shader& other);
    ~Shader();

    static Shader load(const Graphics& gfx, const PGE::String& path);

    PGE::Shader* operator->() const;

    PGE::Shader* getInternal() const;

    bool isTracking() const;
};

#endif // SHADER_H_INCLUDED