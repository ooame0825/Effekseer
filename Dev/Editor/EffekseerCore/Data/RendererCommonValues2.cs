using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Effekseer.Data
{
    public class RendererCommonValues2
    {
        [Name(language = Language.Japanese, value = "合成用\n\n色/歪み画像")]
        [Description(language = Language.Japanese, value = "合成用の色/歪みを表す画像2")]
        [Name(language = Language.English, value = "Texture2")]
        [Description(language = Language.English, value = "Image that represents color/distortion2")]
        public Value.PathForImage ColorTexture2
        {
            get;
            private set;
        }

        [Name(language = Language.Japanese, value = "合成用\n\nαテクスチャ")]
        [Description(language = Language.Japanese, value = "α値を使用する画像2")]
        [Name(language = Language.English, value = "αTexture2")]
        [Description(language = Language.English, value = "Image that represents α2")]
        public Value.PathForImage AlphaTexture2
        {
            get;
            private set;
        }

        [Selector(ID = 0)]
        [Name(language = Language.Japanese, value = "ブレンドタイプ")]
        [Name(language = Language.English, value = "BlendType")]
        public Value.Enum<BlendType> BlendInType
        {
            get;
            private set;
        }

        [Name(language = Language.Japanese, value = "フィルタ")]
        [Name(language = Language.English, value = "Filter")]
        public Value.Enum<FilterType> Filter { get; private set; }

        [Name(language = Language.Japanese, value = "外側")]
        [Name(language = Language.English, value = "Wrap")]
        public Value.Enum<WrapType> Wrap { get; private set; }

        [Selector(ID = 2)]
        [Name(language = Language.Japanese, value = "UV")]
        [Name(language = Language.English, value = "UV")]
        public Value.Enum<UVType> UV
        {
            get;
            private set;
        }

        [Selected(ID = 2, Value = 0)]
        [IO(Export = true)]
        public UVDefaultParamater UVDefault { get; private set; }

        [Selected(ID = 2, Value = 1)]
        [IO(Export = true)]
        public UVFixedParamater UVFixed { get; private set; }

        [Selected(ID = 2, Value = 2)]
        [IO(Export = true)]
        public UVAnimationParamater UVAnimation { get; private set; }

        [Selected(ID = 2, Value = 3)]
        [IO(Export = true)]
        public UVScrollParamater UVScroll { get; private set; }

        [Selected(ID = 2, Value = 4)]
        [IO(Export = true)]
        public UVFCurveParamater UVFCurve { get; private set; }

        internal RendererCommonValues2()
        {
            ColorTexture2 = new Value.PathForImage(Properties.Resources.ImageFilter, true, "");
            AlphaTexture2 = new Value.PathForImage(Properties.Resources.ImageFilter, true, "");

            BlendInType = new Value.Enum<BlendType>(BlendType.AlphaBlend);
            Filter = new Value.Enum<FilterType>(FilterType.Linear);
            Wrap = new Value.Enum<WrapType>(WrapType.Repeat);

            UV = new Value.Enum<UVType>();

            UVDefault = new UVDefaultParamater();
            UVFixed = new UVFixedParamater();
            UVAnimation = new UVAnimationParamater();
            UVScroll = new UVScrollParamater();
            UVFCurve = new UVFCurveParamater();
        }

        public class UVDefaultParamater
        {
        }

        public class UVFixedParamater
        {
            [Name(value = "始点", language = Language.Japanese)]
            [Name(value = "Start", language = Language.English)]
            public Value.Vector2D Start { get; private set; }
            [Name(value = "大きさ", language = Language.Japanese)]
            [Name(value = "Size", language = Language.English)]
            public Value.Vector2D Size { get; private set; }

            public UVFixedParamater()
            {
                Start = new Value.Vector2D();
                Size = new Value.Vector2D();
            }
        }

        public class UVAnimationParamater
        {
            [Name(value = "始点", language = Language.Japanese)]
            [Name(value = "Start", language = Language.English)]
            public Value.Vector2D Start { get; private set; }
            [Name(value = "大きさ", language = Language.Japanese)]
            [Name(value = "Size", language = Language.English)]
            public Value.Vector2D Size { get; private set; }

            [Name(value = "1枚あたりの時間", language = Language.Japanese)]
            [Name(value = "Frame Length", language = Language.English)]
            public Value.IntWithInifinite FrameLength { get; private set; }

            [Name(value = "横方向枚数", language = Language.Japanese)]
            [Name(value = "X-Count", language = Language.English)]
            public Value.Int FrameCountX { get; private set; }

            [Name(value = "縦方向枚数", language = Language.Japanese)]
            [Name(value = "Y-Count", language = Language.English)]
            public Value.Int FrameCountY { get; private set; }

            [Name(value = "ループ", language = Language.Japanese)]
            [Name(value = "Loop", language = Language.English)]
            public Value.Enum<LoopType> LoopType { get; private set; }

            [Name(value = "開始枚数", language = Language.Japanese)]
            [Name(value = "Start Sheet", language = Language.English)]
            public Value.IntWithRandom StartSheet { get; private set; }

            public UVAnimationParamater()
            {
                Start = new Value.Vector2D();
                Size = new Value.Vector2D();
                FrameLength = new Value.IntWithInifinite(1, false, int.MaxValue, 1);
                FrameCountX = new Value.Int(1, int.MaxValue, 1);
                FrameCountY = new Value.Int(1, int.MaxValue, 1);
                LoopType = new Value.Enum<LoopType>(RendererCommonValues2.LoopType.Once);
                StartSheet = new Value.IntWithRandom(0, int.MaxValue, 0);
            }
        }

        public class UVScrollParamater
        {
            [Name(value = "始点", language = Language.Japanese)]
            [Name(value = "Start", language = Language.English)]
            public Value.Vector2DWithRandom Start { get; private set; }

            [Name(value = "大きさ", language = Language.Japanese)]
            [Name(value = "Size", language = Language.English)]
            public Value.Vector2DWithRandom Size { get; private set; }

            [Name(value = "移動速度", language = Language.Japanese)]
            [Name(value = "Scroll Speed", language = Language.English)]
            public Value.Vector2DWithRandom Speed { get; private set; }

            public UVScrollParamater()
            {
                Start = new Value.Vector2DWithRandom();
                Size = new Value.Vector2DWithRandom();
                Speed = new Value.Vector2DWithRandom();
            }
        }

        public class UVFCurveParamater
        {
            [Name(value = "始点", language = Language.Japanese)]
            [Name(value = "Start", language = Language.English)]
            [IO(Export = true)]
            public Value.FCurveVector2D Start { get; private set; }

            [Name(value = "大きさ", language = Language.Japanese)]
            [Name(value = "Size", language = Language.English)]
            [IO(Export = true)]
            public Value.FCurveVector2D Size { get; private set; }

            public UVFCurveParamater()
            {
                Start = new Value.FCurveVector2D();
                Size = new Value.FCurveVector2D();
            }
        }

        public enum BlendType : int
        {
            [Name(value = "αブレンド", language = Language.Japanese)]
            [Name(value = "AlphaBlend", language = Language.English)]
            AlphaBlend = 0,
            [Name(value = "加算", language = Language.Japanese)]
            [Name(value = "Additive", language = Language.English)]
            Add = 1,
            [Name(value = "減算", language = Language.Japanese)]
            [Name(value = "Subtract", language = Language.English)]
            Sub = 2,
            [Name(value = "乗算", language = Language.Japanese)]
            [Name(value = "Multiply", language = Language.English)]
            Mul = 3,
        }

        public enum FilterType : int
        {
            [Name(value = "最近傍", language = Language.Japanese)]
            [Name(value = "Nearest-Neighbor", language = Language.English)]
            Nearest = 0,
            [Name(value = "線形", language = Language.Japanese)]
            [Name(value = "Linear Interpolation", language = Language.English)]
            Linear = 1,
        }

        public enum WrapType : int
        {
            [Name(value = "繰り返し", language = Language.Japanese)]
            [Name(value = "Repeat", language = Language.English)]
            Repeat = 0,
            [Name(value = "クランプ", language = Language.Japanese)]
            [Name(value = "Clamp", language = Language.English)]
            Clamp = 1,
        }

        public enum UVType : int
        {
            [Name(value = "標準", language = Language.Japanese)]
            [Name(value = "Standard", language = Language.English)]
            Default = 0,
            [Name(value = "固定", language = Language.Japanese)]
            [Name(value = "Fixed", language = Language.English)]
            Fixed = 1,
            [Name(value = "アニメーション", language = Language.Japanese)]
            [Name(value = "Animation", language = Language.English)]
            Animation = 2,
            [Name(value = "スクロール", language = Language.Japanese)]
            [Name(value = "Scroll", language = Language.English)]
            Scroll = 3,
            [Name(value = "Fカーブ", language = Language.Japanese)]
            [Name(value = "F-Curve", language = Language.English)]
            FCurve = 4,
        }

        public enum LoopType : int
        {
            [Name(value = "なし", language = Language.Japanese)]
            [Name(value = "None", language = Language.English)]
            Once = 0,
            [Name(value = "ループ", language = Language.Japanese)]
            [Name(value = "Loop", language = Language.English)]
            Loop = 1,
            [Name(value = "逆ループ", language = Language.Japanese)]
            [Name(value = "Reverse Loop", language = Language.English)]
            ReverceLoop = 2,
        }
    }
}
