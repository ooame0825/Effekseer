#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//   fxc /Zpc /Tps_3_0 /EPS /Fh Shader/EffekseerRenderer.Standard_PS.h
//    Shader/standard_renderer_PS.fx
//
//
// Parameters:
//
//   sampler2D g_sampler[4];
//   float4 g_setTexture[3];
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   g_setTexture c0       3
//   g_sampler    s0       4
//

    ps_3_0
    def c3, -1, -2, -3, -4
    def c4, 0, 1, 0, 0
    dcl_texcoord v0
    dcl_texcoord1 v1.xy
    dcl_2d s0
    dcl_2d s1
    dcl_2d s2
    dcl_2d s3
    frc r0.x, c0.x
    cmp r0.y, -r0.x, c4.x, c4.y
    add r0.x, -r0.x, c0.x
    mov r1.x, c4.x
    cmp r0.y, c0.x, r1.x, r0.y
    add r0.x, r0.y, r0.x
    add r0, r0.x, c3
    texld r2, v1, s0
    mul r3, r2, v0
    texld r4, v1, s1
    mul r1.yzw, r3.xxyz, r4.xxyz
    cmp r1.yzw, -r0_abs.w, r1, r3.xxyz
    mad r5.xyz, v0, r2, -r4
    mad r2.xyz, v0, r2, r4
    lrp r6.xyz, r4.w, r4, r3
    mov oC0.w, r3.w
    cmp r1.yzw, -r0_abs.z, r5.xxyz, r1
    cmp r0.yzw, -r0_abs.y, r2.xxyz, r1
    cmp r0.xyz, -r0_abs.x, r6, r0.yzww
    texld r2, v1, s2
    mul r1.yzw, r0.xxyz, r2.xxyz
    frc r0.w, c1.x
    cmp r3.x, -r0.w, c4.x, c4.y
    add r0.w, -r0.w, c1.x
    cmp r3.x, c1.x, r1.x, r3.x
    add r0.w, r0.w, r3.x
    add r3, r0.w, c3
    cmp r1.yzw, -r3_abs.w, r1, r0.xxyz
    add r4.xyz, r0, -r2
    cmp r1.yzw, -r3_abs.z, r4.xxyz, r1
    add r4.xyz, r0, r2
    lrp r5.xyz, r2.w, r2, r0
    cmp r0.xyz, -r3_abs.y, r4, r1.yzww
    cmp r0.xyz, -r3_abs.x, r5, r0
    texld r2, v1, s3
    add r1.yzw, r0.xxyz, -r2.xxyz
    mul r3.xyz, r0, r2
    frc r0.w, c2.x
    cmp r3.w, -r0.w, c4.x, c4.y
    add r0.w, -r0.w, c2.x
    cmp r1.x, c2.x, r1.x, r3.w
    add r0.w, r0.w, r1.x
    add r4, r0.w, c3
    cmp r3.xyz, -r4_abs.w, r3, r0
    cmp r1.xyz, -r4_abs.z, r1.yzww, r3
    add r3.xyz, r0, r2
    lrp r5.xyz, r2.w, r2, r0
    cmp r0.xyz, -r4_abs.y, r3, r1
    cmp oC0.xyz, -r4_abs.x, r5, r0

// approximately 49 instruction slots used (4 texture, 45 arithmetic)
#endif

const BYTE g_ps30_PS[] =
{
      0,   3, 255, 255, 254, 255, 
     47,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 135,   0, 
      0,   0,   0,   3, 255, 255, 
      2,   0,   0,   0,  28,   0, 
      0,   0,  16,   1,   0,   0, 
    128,   0,   0,   0,  68,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   2,   0,  80,   0, 
      0,   0,   0,   0,   0,   0, 
     96,   0,   0,   0,   2,   0, 
      0,   0,   3,   0,   2,   0, 
    112,   0,   0,   0,   0,   0, 
      0,   0, 103,  95, 115,  97, 
    109, 112, 108, 101, 114,   0, 
    171, 171,   4,   0,  12,   0, 
      1,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
    103,  95, 115, 101, 116,  84, 
    101, 120, 116, 117, 114, 101, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0, 112, 115,  95,  51, 
     95,  48,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  57,  46,  50,  57, 
     46,  57,  53,  50,  46,  51, 
     49,  49,  49,   0,  81,   0, 
      0,   5,   3,   0,  15, 160, 
      0,   0, 128, 191,   0,   0, 
      0, 192,   0,   0,  64, 192, 
      0,   0, 128, 192,  81,   0, 
      0,   5,   4,   0,  15, 160, 
      0,   0,   0,   0,   0,   0, 
    128,  63,   0,   0,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   1, 128, 
      1,   0,   3, 144,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      1,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      2,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      3,   8,  15, 160,  19,   0, 
      0,   2,   0,   0,   1, 128, 
      0,   0,   0, 160,  88,   0, 
      0,   4,   0,   0,   2, 128, 
      0,   0,   0, 129,   4,   0, 
      0, 160,   4,   0,  85, 160, 
      2,   0,   0,   3,   0,   0, 
      1, 128,   0,   0,   0, 129, 
      0,   0,   0, 160,   1,   0, 
      0,   2,   1,   0,   1, 128, 
      4,   0,   0, 160,  88,   0, 
      0,   4,   0,   0,   2, 128, 
      0,   0,   0, 160,   1,   0, 
      0, 128,   0,   0,  85, 128, 
      2,   0,   0,   3,   0,   0, 
      1, 128,   0,   0,  85, 128, 
      0,   0,   0, 128,   2,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0,   0, 128,   3,   0, 
    228, 160,  66,   0,   0,   3, 
      2,   0,  15, 128,   1,   0, 
    228, 144,   0,   8, 228, 160, 
      5,   0,   0,   3,   3,   0, 
     15, 128,   2,   0, 228, 128, 
      0,   0, 228, 144,  66,   0, 
      0,   3,   4,   0,  15, 128, 
      1,   0, 228, 144,   1,   8, 
    228, 160,   5,   0,   0,   3, 
      1,   0,  14, 128,   3,   0, 
    144, 128,   4,   0, 144, 128, 
     88,   0,   0,   4,   1,   0, 
     14, 128,   0,   0, 255, 140, 
      1,   0, 228, 128,   3,   0, 
    144, 128,   4,   0,   0,   4, 
      5,   0,   7, 128,   0,   0, 
    228, 144,   2,   0, 228, 128, 
      4,   0, 228, 129,   4,   0, 
      0,   4,   2,   0,   7, 128, 
      0,   0, 228, 144,   2,   0, 
    228, 128,   4,   0, 228, 128, 
     18,   0,   0,   4,   6,   0, 
      7, 128,   4,   0, 255, 128, 
      4,   0, 228, 128,   3,   0, 
    228, 128,   1,   0,   0,   2, 
      0,   8,   8, 128,   3,   0, 
    255, 128,  88,   0,   0,   4, 
      1,   0,  14, 128,   0,   0, 
    170, 140,   5,   0, 144, 128, 
      1,   0, 228, 128,  88,   0, 
      0,   4,   0,   0,  14, 128, 
      0,   0,  85, 140,   2,   0, 
    144, 128,   1,   0, 228, 128, 
     88,   0,   0,   4,   0,   0, 
      7, 128,   0,   0,   0, 140, 
      6,   0, 228, 128,   0,   0, 
    249, 128,  66,   0,   0,   3, 
      2,   0,  15, 128,   1,   0, 
    228, 144,   2,   8, 228, 160, 
      5,   0,   0,   3,   1,   0, 
     14, 128,   0,   0, 144, 128, 
      2,   0, 144, 128,  19,   0, 
      0,   2,   0,   0,   8, 128, 
      1,   0,   0, 160,  88,   0, 
      0,   4,   3,   0,   1, 128, 
      0,   0, 255, 129,   4,   0, 
      0, 160,   4,   0,  85, 160, 
      2,   0,   0,   3,   0,   0, 
      8, 128,   0,   0, 255, 129, 
      1,   0,   0, 160,  88,   0, 
      0,   4,   3,   0,   1, 128, 
      1,   0,   0, 160,   1,   0, 
      0, 128,   3,   0,   0, 128, 
      2,   0,   0,   3,   0,   0, 
      8, 128,   0,   0, 255, 128, 
      3,   0,   0, 128,   2,   0, 
      0,   3,   3,   0,  15, 128, 
      0,   0, 255, 128,   3,   0, 
    228, 160,  88,   0,   0,   4, 
      1,   0,  14, 128,   3,   0, 
    255, 140,   1,   0, 228, 128, 
      0,   0, 144, 128,   2,   0, 
      0,   3,   4,   0,   7, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 129,  88,   0,   0,   4, 
      1,   0,  14, 128,   3,   0, 
    170, 140,   4,   0, 144, 128, 
      1,   0, 228, 128,   2,   0, 
      0,   3,   4,   0,   7, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 128,  18,   0,   0,   4, 
      5,   0,   7, 128,   2,   0, 
    255, 128,   2,   0, 228, 128, 
      0,   0, 228, 128,  88,   0, 
      0,   4,   0,   0,   7, 128, 
      3,   0,  85, 140,   4,   0, 
    228, 128,   1,   0, 249, 128, 
     88,   0,   0,   4,   0,   0, 
      7, 128,   3,   0,   0, 140, 
      5,   0, 228, 128,   0,   0, 
    228, 128,  66,   0,   0,   3, 
      2,   0,  15, 128,   1,   0, 
    228, 144,   3,   8, 228, 160, 
      2,   0,   0,   3,   1,   0, 
     14, 128,   0,   0, 144, 128, 
      2,   0, 144, 129,   5,   0, 
      0,   3,   3,   0,   7, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 128,  19,   0,   0,   2, 
      0,   0,   8, 128,   2,   0, 
      0, 160,  88,   0,   0,   4, 
      3,   0,   8, 128,   0,   0, 
    255, 129,   4,   0,   0, 160, 
      4,   0,  85, 160,   2,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 255, 129,   2,   0, 
      0, 160,  88,   0,   0,   4, 
      1,   0,   1, 128,   2,   0, 
      0, 160,   1,   0,   0, 128, 
      3,   0, 255, 128,   2,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 255, 128,   1,   0, 
      0, 128,   2,   0,   0,   3, 
      4,   0,  15, 128,   0,   0, 
    255, 128,   3,   0, 228, 160, 
     88,   0,   0,   4,   3,   0, 
      7, 128,   4,   0, 255, 140, 
      3,   0, 228, 128,   0,   0, 
    228, 128,  88,   0,   0,   4, 
      1,   0,   7, 128,   4,   0, 
    170, 140,   1,   0, 249, 128, 
      3,   0, 228, 128,   2,   0, 
      0,   3,   3,   0,   7, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 128,  18,   0,   0,   4, 
      5,   0,   7, 128,   2,   0, 
    255, 128,   2,   0, 228, 128, 
      0,   0, 228, 128,  88,   0, 
      0,   4,   0,   0,   7, 128, 
      4,   0,  85, 140,   3,   0, 
    228, 128,   1,   0, 228, 128, 
     88,   0,   0,   4,   0,   8, 
      7, 128,   4,   0,   0, 140, 
      5,   0, 228, 128,   0,   0, 
    228, 128, 255, 255,   0,   0
};
