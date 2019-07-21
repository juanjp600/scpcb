#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <map>

#include <Graphics/Graphics.h>

#include <Texture/Texture.h>
#include <Shader/Shader.h>
#include <Material/Material.h>
#include <Mesh/Mesh.h>

#include <Misc/FileName.h>
#include <Misc/String.h>
#include <Math/Vector.h>
#include <Math/Rectangle.h>

class Font {
    public:
        Font(FT_Library ftLibrary,PGE::Graphics* gfx,const PGE::FileName& fn,int h, PGE::Shader* s);
        ~Font();

        void draw(PGE::String text, PGE::Vector3f pos, PGE::Vector2f scale=PGE::Vector2f::one, PGE::Vector3f rotation=PGE::Vector3f::zero, PGE::Color color=PGE::Color(1.f,1.f,1.f,1.f));
        void draw(PGE::String text, PGE::Vector2f pos, PGE::Vector2f scale=PGE::Vector2f::one,float rotation=0.f, PGE::Color color=PGE::Color(1.f,1.f,1.f,1.f));

        struct Atlas {
            PGE::Texture* texture;
            PGE::Material* material;
            PGE::Mesh* mesh;

            std::vector<PGE::Vertex> vertices;
            std::vector<PGE::Primitive> primitives;
        };

        std::vector<Atlas> atlases;
    private:
        Font();

        struct GlyphData {
            int atlasIndex;
            PGE::Vector2f drawOffset;
            float horizontalAdvance;
            PGE::Rectanglef srcRect;
        };

        PGE::Shader* shader;
        PGE::Shader::Constant* modelMatrixConstant;
        PGE::Shader::Constant* colorConstant;

        const int atlasDims = 32;

        void renderAtlas(long chr);

        int height;
        FT_Face freeTypeFace;

        std::map<long,GlyphData> glyphData;

        PGE::Graphics* graphics;

        PGE::FileName filename;
};

#endif
