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
//   float4 g_MultiTexBlendType;
//   sampler2D g_sampler[4];
//   float4 g_setTexture[4];
//
//
// Registers:
//
//   Name                Reg   Size
//   ------------------- ----- ----
//   g_setTexture        c0       4
//   g_MultiTexBlendType c4       1
//   g_sampler           s0       4
//

    ps_3_0
    def c0, 0, 1, -1, 0
    def c5, -1, -2, -3, 0
    dcl_texcoord v0
    dcl_texcoord1 v1.xy
    dcl_2d s0
    dcl_2d s1
    dcl_2d s2
    dcl_2d s3
    texld r0, v1, s0
    mul r1, r0, v0
    frc r0.w, c1.x
    add r2.x, -r0.w, c1.x
    cmp r0.w, -r0.w, c0.x, c0.y
    mov r3.x, c0.x
    cmp r0.w, c1.x, r3.x, r0.w
    add r0.w, r0.w, r2.x
    if_eq r0.w, c0.y
      texld r2, v1, s1
      mov oC0.w, r2.w
    else
      mov oC0.w, r1.w
    endif
    frc r0.w, c2.x
    add r1.w, -r0.w, c2.x
    cmp r0.w, -r0.w, c0.x, c0.y
    cmp r0.w, c2.x, r3.x, r0.w
    add r0.w, r0.w, r1.w
    add r1.w, r0.w, c0.z
    if_eq r0.w, c0.y
      texld r2, v1, s2
    else
      mov r2, c0.x
    endif
    frc r3.y, c3.x
    add r3.z, -r3.y, c3.x
    cmp r3.y, -r3.y, c0.x, c0.y
    cmp r3.y, c3.x, r3.x, r3.y
    add r3.y, r3.y, r3.z
    if_eq r3.y, c0.y
      if_eq r0.w, c0.y
        texld r4, v1, s3
        mov r2.w, r4.w
      endif
    endif
    frc r0.w, c4.x
    add r3.y, -r0.w, c4.x
    cmp r0.w, -r0.w, c0.x, c0.y
    cmp r0.w, c4.x, r3.x, r0.w
    add r0.w, r0.w, r3.y
    mul r3.xyz, r2.w, r2
    lrp r4.xyz, r2.w, r2, r1
    add r2.xyz, r0.w, c5
    mad r5.xyz, v0, r0, r3
    mad r0.xyz, v0, r0, -r3
    mul r3.xyz, r1, r3
    cmp r3.xyz, -r2_abs.z, r3, r1
    cmp r0.xyz, -r2_abs.y, r0, r3
    cmp r0.xyz, -r2_abs.x, r5, r0
    cmp r0.xyz, -r0_abs.w, r4, r0
    cmp oC0.xyz, -r1_abs.w, r0, r1

// approximately 60 instruction slots used (4 texture, 56 arithmetic)
#endif

const BYTE g_ps30_PS[] =
{
      0,   3, 255, 255, 254, 255, 
     61,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 191,   0, 
      0,   0,   0,   3, 255, 255, 
      3,   0,   0,   0,  28,   0, 
      0,   0,  16,   1,   0,   0, 
    184,   0,   0,   0,  88,   0, 
      0,   0,   2,   0,   4,   0, 
      1,   0,  18,   0, 108,   0, 
      0,   0,   0,   0,   0,   0, 
    124,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   2,   0, 
    136,   0,   0,   0,   0,   0, 
      0,   0, 152,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      6,   0, 168,   0,   0,   0, 
      0,   0,   0,   0, 103,  95, 
     77, 117, 108, 116, 105,  84, 
    101, 120,  66, 108, 101, 110, 
    100,  84, 121, 112, 101,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 103,  95, 
    115,  97, 109, 112, 108, 101, 
    114,   0, 171, 171,   4,   0, 
     12,   0,   1,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0, 103,  95, 115, 101, 
    116,  84, 101, 120, 116, 117, 
    114, 101,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   4,   0,   0,   0, 
      0,   0,   0,   0, 112, 115, 
     95,  51,  95,  48,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  57,  46, 
     50,  57,  46,  57,  53,  50, 
     46,  51,  49,  49,  49,   0, 
     81,   0,   0,   5,   0,   0, 
     15, 160,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
    128, 191,   0,   0,   0,   0, 
     81,   0,   0,   5,   5,   0, 
     15, 160,   0,   0, 128, 191, 
      0,   0,   0, 192,   0,   0, 
     64, 192,   0,   0,   0,   0, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      1, 128,   1,   0,   3, 144, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   1,   8,  15, 160, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   2,   8,  15, 160, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   3,   8,  15, 160, 
     66,   0,   0,   3,   0,   0, 
     15, 128,   1,   0, 228, 144, 
      0,   8, 228, 160,   5,   0, 
      0,   3,   1,   0,  15, 128, 
      0,   0, 228, 128,   0,   0, 
    228, 144,  19,   0,   0,   2, 
      0,   0,   8, 128,   1,   0, 
      0, 160,   2,   0,   0,   3, 
      2,   0,   1, 128,   0,   0, 
    255, 129,   1,   0,   0, 160, 
     88,   0,   0,   4,   0,   0, 
      8, 128,   0,   0, 255, 129, 
      0,   0,   0, 160,   0,   0, 
     85, 160,   1,   0,   0,   2, 
      3,   0,   1, 128,   0,   0, 
      0, 160,  88,   0,   0,   4, 
      0,   0,   8, 128,   1,   0, 
      0, 160,   3,   0,   0, 128, 
      0,   0, 255, 128,   2,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 255, 128,   2,   0, 
      0, 128,  41,   0,   2,   2, 
      0,   0, 255, 128,   0,   0, 
     85, 160,  66,   0,   0,   3, 
      2,   0,  15, 128,   1,   0, 
    228, 144,   1,   8, 228, 160, 
      1,   0,   0,   2,   0,   8, 
      8, 128,   2,   0, 255, 128, 
     42,   0,   0,   0,   1,   0, 
      0,   2,   0,   8,   8, 128, 
      1,   0, 255, 128,  43,   0, 
      0,   0,  19,   0,   0,   2, 
      0,   0,   8, 128,   2,   0, 
      0, 160,   2,   0,   0,   3, 
      1,   0,   8, 128,   0,   0, 
    255, 129,   2,   0,   0, 160, 
     88,   0,   0,   4,   0,   0, 
      8, 128,   0,   0, 255, 129, 
      0,   0,   0, 160,   0,   0, 
     85, 160,  88,   0,   0,   4, 
      0,   0,   8, 128,   2,   0, 
      0, 160,   3,   0,   0, 128, 
      0,   0, 255, 128,   2,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 255, 128,   1,   0, 
    255, 128,   2,   0,   0,   3, 
      1,   0,   8, 128,   0,   0, 
    255, 128,   0,   0, 170, 160, 
     41,   0,   2,   2,   0,   0, 
    255, 128,   0,   0,  85, 160, 
     66,   0,   0,   3,   2,   0, 
     15, 128,   1,   0, 228, 144, 
      2,   8, 228, 160,  42,   0, 
      0,   0,   1,   0,   0,   2, 
      2,   0,  15, 128,   0,   0, 
      0, 160,  43,   0,   0,   0, 
     19,   0,   0,   2,   3,   0, 
      2, 128,   3,   0,   0, 160, 
      2,   0,   0,   3,   3,   0, 
      4, 128,   3,   0,  85, 129, 
      3,   0,   0, 160,  88,   0, 
      0,   4,   3,   0,   2, 128, 
      3,   0,  85, 129,   0,   0, 
      0, 160,   0,   0,  85, 160, 
     88,   0,   0,   4,   3,   0, 
      2, 128,   3,   0,   0, 160, 
      3,   0,   0, 128,   3,   0, 
     85, 128,   2,   0,   0,   3, 
      3,   0,   2, 128,   3,   0, 
     85, 128,   3,   0, 170, 128, 
     41,   0,   2,   2,   3,   0, 
     85, 128,   0,   0,  85, 160, 
     41,   0,   2,   2,   0,   0, 
    255, 128,   0,   0,  85, 160, 
     66,   0,   0,   3,   4,   0, 
     15, 128,   1,   0, 228, 144, 
      3,   8, 228, 160,   1,   0, 
      0,   2,   2,   0,   8, 128, 
      4,   0, 255, 128,  43,   0, 
      0,   0,  43,   0,   0,   0, 
     19,   0,   0,   2,   0,   0, 
      8, 128,   4,   0,   0, 160, 
      2,   0,   0,   3,   3,   0, 
      2, 128,   0,   0, 255, 129, 
      4,   0,   0, 160,  88,   0, 
      0,   4,   0,   0,   8, 128, 
      0,   0, 255, 129,   0,   0, 
      0, 160,   0,   0,  85, 160, 
     88,   0,   0,   4,   0,   0, 
      8, 128,   4,   0,   0, 160, 
      3,   0,   0, 128,   0,   0, 
    255, 128,   2,   0,   0,   3, 
      0,   0,   8, 128,   0,   0, 
    255, 128,   3,   0,  85, 128, 
      5,   0,   0,   3,   3,   0, 
      7, 128,   2,   0, 255, 128, 
      2,   0, 228, 128,  18,   0, 
      0,   4,   4,   0,   7, 128, 
      2,   0, 255, 128,   2,   0, 
    228, 128,   1,   0, 228, 128, 
      2,   0,   0,   3,   2,   0, 
      7, 128,   0,   0, 255, 128, 
      5,   0, 228, 160,   4,   0, 
      0,   4,   5,   0,   7, 128, 
      0,   0, 228, 144,   0,   0, 
    228, 128,   3,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
      7, 128,   0,   0, 228, 144, 
      0,   0, 228, 128,   3,   0, 
    228, 129,   5,   0,   0,   3, 
      3,   0,   7, 128,   1,   0, 
    228, 128,   3,   0, 228, 128, 
     88,   0,   0,   4,   3,   0, 
      7, 128,   2,   0, 170, 140, 
      3,   0, 228, 128,   1,   0, 
    228, 128,  88,   0,   0,   4, 
      0,   0,   7, 128,   2,   0, 
     85, 140,   0,   0, 228, 128, 
      3,   0, 228, 128,  88,   0, 
      0,   4,   0,   0,   7, 128, 
      2,   0,   0, 140,   5,   0, 
    228, 128,   0,   0, 228, 128, 
     88,   0,   0,   4,   0,   0, 
      7, 128,   0,   0, 255, 140, 
      4,   0, 228, 128,   0,   0, 
    228, 128,  88,   0,   0,   4, 
      0,   8,   7, 128,   1,   0, 
    255, 140,   0,   0, 228, 128, 
      1,   0, 228, 128, 255, 255, 
      0,   0
};
