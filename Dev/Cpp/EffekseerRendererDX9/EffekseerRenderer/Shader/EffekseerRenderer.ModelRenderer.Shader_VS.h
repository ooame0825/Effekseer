#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//   fxc /Zpc /Tvs_3_0 /EVS /Fh
//    Shader/EffekseerRenderer.ModelRenderer.Shader_VS.h
//    Shader/model_renderer_VS.fx
//
//
// Parameters:
//
//   float4 fBlendUV[20];
//   float4 fModelColor[20];
//   float4 fUV[20];
//   float4x4 mCameraProj;
//   float4x4 mModel[20];
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   mCameraProj  c0       4
//   mModel       c4      80
//   fUV          c84     20
//   fBlendUV     c104    20
//   fModelColor  c124    20
//

    vs_3_0
    def c144, 4, 0, 0, 0
    dcl_position v0
    dcl_texcoord v1
    dcl_normal3 v2
    dcl_blendindices v3
    dcl_position o0
    dcl_texcoord o1
    dcl_color o2
    mova a0.x, v3.x
    mul o2, v2, c124[a0.x]
    mul r0.x, c144.x, v3.x
    mova a0.y, r0.x
    mul r0, v0.y, c5[a0.y]
    mad r0, c4[a0.y], v0.x, r0
    mad r0, c6[a0.y], v0.z, r0
    add r0, r0, c7[a0.y]
    mul r1, r0.y, c1
    mad r1, c0, r0.x, r1
    mad r1, c2, r0.z, r1
    mad o0, c3, r0.w, r1
    mad o1.xy, v1, c84[a0.x].zwzw, c84[a0.x]
    mad o1.zw, v1.xyxy, c104[a0.x], c104[a0.x].xyxy

// approximately 14 instruction slots used
#endif

const BYTE g_vs30_VS[] =
{
      0,   3, 254, 255, 254, 255, 
     79,   0,  67,  84,  65,  66, 
     28,   0,   0,   0,   7,   1, 
      0,   0,   0,   3, 254, 255, 
      5,   0,   0,   0,  28,   0, 
      0,   0,  16,   1,   0,   0, 
      0,   1,   0,   0, 128,   0, 
      0,   0,   2,   0, 104,   0, 
     20,   0, 162,   1, 140,   0, 
      0,   0,   0,   0,   0,   0, 
    156,   0,   0,   0,   2,   0, 
    124,   0,  20,   0, 242,   1, 
    168,   0,   0,   0,   0,   0, 
      0,   0, 184,   0,   0,   0, 
      2,   0,  84,   0,  20,   0, 
     82,   1, 188,   0,   0,   0, 
      0,   0,   0,   0, 204,   0, 
      0,   0,   2,   0,   0,   0, 
      4,   0,   2,   0, 216,   0, 
      0,   0,   0,   0,   0,   0, 
    232,   0,   0,   0,   2,   0, 
      4,   0,  80,   0,  18,   0, 
    240,   0,   0,   0,   0,   0, 
      0,   0, 102,  66, 108, 101, 
    110, 100,  85,  86,   0, 171, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,  20,   0, 
      0,   0,   0,   0,   0,   0, 
    102,  77, 111, 100, 101, 108, 
     67, 111, 108, 111, 114,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,  20,   0,   0,   0, 
      0,   0,   0,   0, 102,  85, 
     86,   0,   1,   0,   3,   0, 
      1,   0,   4,   0,  20,   0, 
      0,   0,   0,   0,   0,   0, 
    109,  67,  97, 109, 101, 114, 
     97,  80, 114, 111, 106,   0, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 109,  77, 
    111, 100, 101, 108,   0, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,  20,   0,   0,   0, 
      0,   0,   0,   0, 118, 115, 
     95,  51,  95,  48,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  57,  46, 
     50,  57,  46,  57,  53,  50, 
     46,  51,  49,  49,  49,   0, 
     81,   0,   0,   5, 144,   0, 
     15, 160,   0,   0, 128,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   1,   0,  15, 144, 
     31,   0,   0,   2,   3,   0, 
      3, 128,   2,   0,  15, 144, 
     31,   0,   0,   2,   2,   0, 
      0, 128,   3,   0,  15, 144, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,  15, 224, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   1,   0,  15, 224, 
     31,   0,   0,   2,  10,   0, 
      0, 128,   2,   0,  15, 224, 
     46,   0,   0,   2,   0,   0, 
      1, 176,   3,   0,   0, 144, 
      5,   0,   0,   4,   2,   0, 
     15, 224,   2,   0, 228, 144, 
    124,  32, 228, 160,   0,   0, 
      0, 176,   5,   0,   0,   3, 
      0,   0,   1, 128, 144,   0, 
      0, 160,   3,   0,   0, 144, 
     46,   0,   0,   2,   0,   0, 
      2, 176,   0,   0,   0, 128, 
      5,   0,   0,   4,   0,   0, 
     15, 128,   0,   0,  85, 144, 
      5,  32, 228, 160,   0,   0, 
     85, 176,   4,   0,   0,   5, 
      0,   0,  15, 128,   4,  32, 
    228, 160,   0,   0,  85, 176, 
      0,   0,   0, 144,   0,   0, 
    228, 128,   4,   0,   0,   5, 
      0,   0,  15, 128,   6,  32, 
    228, 160,   0,   0,  85, 176, 
      0,   0, 170, 144,   0,   0, 
    228, 128,   2,   0,   0,   4, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   7,  32, 228, 160, 
      0,   0,  85, 176,   5,   0, 
      0,   3,   1,   0,  15, 128, 
      0,   0,  85, 128,   1,   0, 
    228, 160,   4,   0,   0,   4, 
      1,   0,  15, 128,   0,   0, 
    228, 160,   0,   0,   0, 128, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      2,   0, 228, 160,   0,   0, 
    170, 128,   1,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 224,   3,   0, 228, 160, 
      0,   0, 255, 128,   1,   0, 
    228, 128,   4,   0,   0,   6, 
      1,   0,   3, 224,   1,   0, 
    228, 144,  84,  32, 238, 160, 
      0,   0,   0, 176,  84,  32, 
    228, 160,   0,   0,   0, 176, 
      4,   0,   0,   6,   1,   0, 
     12, 224,   1,   0,  68, 144, 
    104,  32, 228, 160,   0,   0, 
      0, 176, 104,  32,  68, 160, 
      0,   0,   0, 176, 255, 255, 
      0,   0
};
