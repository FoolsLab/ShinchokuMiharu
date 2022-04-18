#include "Text.hpp"

MisakiFont::MisakiFont()
    : img201("./assets/k8x12_jisx0201.png", GL_NEAREST),
      img208("./assets/k8x12_jisx0208.png", GL_NEAREST) {}

bool MisakiFont::Draw(IRenderContext& ctx, Point pos, Size rect, float fontsize,
                      std::string str) const {
    const Size szBase = {4.0f, 12.0f};
    Point cpos = pos;
    for (size_t i = 0; i < str.length(); i++) {
        // shift_jis multibyte char
        int bytenum =
            ((str[i] & 0xE0) == 0x80 || (str[i] & 0xE0) == 0xE0) ? 2 : 1;

        Size srcCSz = {szBase.x * bytenum, szBase.y};
        Size dispCSz = {srcCSz.x * fontsize, srcCSz.y * fontsize};
        if (cpos.x + dispCSz.x > pos.x + rect.x) {
            cpos.x = pos.x;
            cpos.y += dispCSz.y;
        }
        if(bytenum == 1 && str[i] == '\n'){
            cpos.x = pos.x;
            cpos.y += dispCSz.y;
            continue;
        }

        if (bytenum == 1) {
            int code = (unsigned char)str[i];

            ctx.Draw(img201, cpos,
                     {(code % 16) * srcCSz.x, (code / 16) * srcCSz.y},
                     srcCSz, fontsize);
        } else {
            int code_b1 = (unsigned char)str[i];
            int code_b2 = (unsigned char)str[i + 1];
            int code_ku, code_ten;

            if (code_b2 < 0x80) {
                code_ku = (code_b1 - 0x81) * 2;
                code_ten = code_b2 - 0x40;
            } else if(code_b2 < 0x9F) {
                code_ku = (code_b1 - 0x81) * 2;
                code_ten = code_b2 - 0x80 + 63;
            } else {
                code_ku = (code_b1 - 0x81) * 2 + 1;
                code_ten = code_b2 - 0x9F;
            }

            ctx.Draw(img208, cpos,
                     {code_ten * srcCSz.x,
                      code_ku * srcCSz.y},
                     srcCSz, fontsize);
        }
        cpos.x += dispCSz.x;

        // extra bytes
        i += (bytenum - 1);
    }

    return false;
};
