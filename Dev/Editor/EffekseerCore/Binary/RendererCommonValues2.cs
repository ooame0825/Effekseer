using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Effekseer.Utl;

namespace Effekseer.Binary
{
    class RendererCommonValues2
    {
        public static byte[] GetBytes(Data.RendererCommonValues2 value, Dictionary<string, int> texture_and_index, Dictionary<string, int> distortionTexture_and_index)
        {
            List<byte[]> data = new List<byte[]>();

            var texInfo = new TextureInformation();
            var hasTexture = true;

            // ColorTextute
            if (value.ColorTexture2.RelativePath != string.Empty &&
            texture_and_index.ContainsKey(value.ColorTexture2.RelativePath) &&
            texInfo.Load(value.ColorTexture2.AbsolutePath))
            {
                data.Add(texture_and_index[value.ColorTexture2.RelativePath].GetBytes());
                hasTexture = true;
            }
            else
            {
                data.Add((-1).GetBytes());
                hasTexture = false;
            }
            // AlphaTexture
            if (value.AlphaTexture2.RelativePath != string.Empty &&
                texture_and_index.ContainsKey(value.AlphaTexture2.RelativePath) &&
                texInfo.Load(value.AlphaTexture2.AbsolutePath))
            {
                data.Add(texture_and_index[value.AlphaTexture2.RelativePath].GetBytes());
                hasTexture = true;
            }
            else
            {
                data.Add((-1).GetBytes());
                //hasTexture = false;
            }

            // BlendMode
            data.Add(value.BlendInType);

            // Filter
            data.Add(value.Filter);

            // Wrap
            data.Add(value.Wrap);

            // UV
            if (hasTexture)
            {
                var width = (float)texInfo.Width;
                var height = (float)texInfo.Height;

                // UV type
                data.Add(value.UV);

                // Default
                if (value.UV.Value == Data.RendererCommonValues2.UVType.Default)
                {
                }
                // UV Fixed
                else if (value.UV.Value == Data.RendererCommonValues2.UVType.Fixed)
                {
                    var value_ = value.UVFixed;
                    data.Add((value_.Start.X / width).GetBytes());
                    data.Add((value_.Start.Y / height).GetBytes());
                    data.Add((value_.Size.X / width).GetBytes());
                    data.Add((value_.Size.Y / height).GetBytes());
                }
                // UV Animation
                else if (value.UV.Value == Data.RendererCommonValues2.UVType.Animation)
                {
                    var value_ = value.UVAnimation;
                    data.Add((value_.Start.X / width).GetBytes());
                    data.Add((value_.Start.Y / height).GetBytes());
                    data.Add((value_.Size.X / width).GetBytes());
                    data.Add((value_.Size.Y / height).GetBytes());

                    if (value_.FrameLength.Infinite)
                    {
                        var inf = int.MaxValue / 100;
                        data.Add(inf.GetBytes());
                    }
                    else
                    {
                        data.Add(value_.FrameLength.Value.Value.GetBytes());
                    }

                    data.Add(value_.FrameCountX.Value.GetBytes());
                    data.Add(value_.FrameCountY.Value.GetBytes());
                    data.Add(value_.LoopType);

                    data.Add(value_.StartSheet.Max.GetBytes());
                    data.Add(value_.StartSheet.Min.GetBytes());

                }
                // UV Scroll
                else if (value.UV.Value == Data.RendererCommonValues2.UVType.Scroll)
                {
                    var value_ = value.UVScroll;
                    data.Add((value_.Start.X.Max / width).GetBytes());
                    data.Add((value_.Start.Y.Max / height).GetBytes());
                    data.Add((value_.Start.X.Min / width).GetBytes());
                    data.Add((value_.Start.Y.Min / height).GetBytes());

                    data.Add((value_.Size.X.Max / width).GetBytes());
                    data.Add((value_.Size.Y.Max / height).GetBytes());
                    data.Add((value_.Size.X.Min / width).GetBytes());
                    data.Add((value_.Size.Y.Min / height).GetBytes());

                    data.Add((value_.Speed.X.Max / width).GetBytes());
                    data.Add((value_.Speed.Y.Max / height).GetBytes());
                    data.Add((value_.Speed.X.Min / width).GetBytes());
                    data.Add((value_.Speed.Y.Min / height).GetBytes());
                }
                // FCurve
                else if (value.UV.Value == Data.RendererCommonValues2.UVType.FCurve)
                {
                    {
                        var value_ = value.UVFCurve.Start;
                        var bytes1 = value_.GetBytes(1.0f / width);
                        List<byte[]> _data = new List<byte[]>();
                        data.Add(bytes1);
                    }

                    {
                        var value_ = value.UVFCurve.Size;
                        var bytes1 = value_.GetBytes(1.0f / height);
                        List<byte[]> _data = new List<byte[]>();
                        data.Add(bytes1);
                    }
                }
            }
            else
            {
                // None
                data.Add(((int)Data.RendererCommonValues.UVType.Default).GetBytes());
            }

            // [TODO] Distotion

            return data.ToArray().ToArray();
        }
    }
}
