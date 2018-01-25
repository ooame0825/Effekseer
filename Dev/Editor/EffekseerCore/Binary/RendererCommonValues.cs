﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Effekseer.Utl;


namespace Effekseer.Binary
{
	class RendererCommonValues
	{
		public static byte[] GetBytes(Data.RendererCommonValues value, Dictionary<string, int> texture_and_index, Dictionary<string, int> distortionTexture_and_index)
		{
			List<byte[]> data = new List<byte[]>();

			var texInfo = new TextureInformation();
			var hasTexture = true;

			// テクスチャ番号
			if (value.Distortion.Value)
			{
				if (value.ColorTexture.RelativePath != string.Empty &&
				distortionTexture_and_index.ContainsKey(value.ColorTexture.RelativePath) &&
				texInfo.Load(value.ColorTexture.AbsolutePath))
				{
					data.Add(distortionTexture_and_index[value.ColorTexture.RelativePath].GetBytes());
					hasTexture = true;
				}
				else
				{
					data.Add((-1).GetBytes());
					hasTexture = false;
				}


                // AlphaTexture
                if (value.AlphaTexture.RelativePath != string.Empty &&
                    texture_and_index.ContainsKey(value.AlphaTexture.RelativePath) &&
                    texInfo.Load(value.AlphaTexture.AbsolutePath))
                {
                    data.Add(texture_and_index[value.AlphaTexture.RelativePath].GetBytes());
                    hasTexture = true;
                }
                else
                {
                    data.Add((-1).GetBytes());
                    //hasTexture = false;
                }

                // texture 2
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
                    //hasTexture = false;
                }

                // texture 4
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

            }
            else
			{
				if (value.ColorTexture.RelativePath != string.Empty &&
					texture_and_index.ContainsKey(value.ColorTexture.RelativePath) &&
					texInfo.Load(value.ColorTexture.AbsolutePath))
				{
					data.Add(texture_and_index[value.ColorTexture.RelativePath].GetBytes());
					hasTexture = true;
				}
				else
				{
					data.Add((-1).GetBytes());
					hasTexture = false;
				}

                // AlphaTexture
                if (value.AlphaTexture.RelativePath != string.Empty &&
                    texture_and_index.ContainsKey(value.AlphaTexture.RelativePath) &&
                    texInfo.Load(value.AlphaTexture.AbsolutePath))
                {
                    data.Add(texture_and_index[value.AlphaTexture.RelativePath].GetBytes());
                    hasTexture = true;
                }
                else
                {
                    data.Add((-1).GetBytes());
                   //hasTexture = false;
                }

                // texture 2
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
                    //hasTexture = false;
                }

                // alpha texture 2
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
            }
			

			data.Add(value.AlphaBlend);
			data.Add(value.Filter);
			data.Add(value.Wrap);

			if (value.ZTest.GetValue())
			{
				data.Add((1).GetBytes());
			}
			else
			{
				data.Add((0).GetBytes());
			}

			if (value.ZWrite.GetValue())
			{
				data.Add((1).GetBytes());
			}
			else
			{
				data.Add((0).GetBytes());
			}

			data.Add(value.FadeInType);
			if (value.FadeInType.Value == Data.RendererCommonValues.FadeType.Use)
			{
				data.Add(value.FadeIn.Frame.GetBytes());

				var easing = Utl.MathUtl.Easing((float)value.FadeIn.StartSpeed.Value, (float)value.FadeIn.EndSpeed.Value);
				data.Add(BitConverter.GetBytes(easing[0]));
				data.Add(BitConverter.GetBytes(easing[1]));
				data.Add(BitConverter.GetBytes(easing[2]));
			}

			data.Add(value.FadeOutType);
			if (value.FadeOutType.Value == Data.RendererCommonValues.FadeType.Use)
			{
				data.Add(value.FadeOut.Frame.GetBytes());

				var easing = Utl.MathUtl.Easing((float)value.FadeOut.StartSpeed.Value, (float)value.FadeOut.EndSpeed.Value);
				data.Add(BitConverter.GetBytes(easing[0]));
				data.Add(BitConverter.GetBytes(easing[1]));
				data.Add(BitConverter.GetBytes(easing[2]));
			}

			if (hasTexture)
			{
				var width = (float)texInfo.Width;
				var height = (float)texInfo.Height;

				data.Add(value.UV);
				if (value.UV.Value == Data.RendererCommonValues.UVType.Default)
				{
				}
				else if (value.UV.Value == Data.RendererCommonValues.UVType.Fixed)
				{
					var value_ = value.UVFixed;
					data.Add((value_.Start.X / width).GetBytes());
					data.Add((value_.Start.Y / height).GetBytes());
					data.Add((value_.Size.X / width).GetBytes());
					data.Add((value_.Size.Y / height).GetBytes());
				}
				else if (value.UV.Value == Data.RendererCommonValues.UVType.Animation)
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
				else if (value.UV.Value == Data.RendererCommonValues.UVType.Scroll)
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
				else if (value.UV.Value == Data.RendererCommonValues.UVType.FCurve)
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
				data.Add(((int)Data.RendererCommonValues.UVType.Default).GetBytes());
			}

			// Inheritance
			data.Add(value.ColorInheritType.GetValueAsInt().GetBytes());

			// 歪み
			if (value.Distortion.GetValue())
			{
				data.Add((1).GetBytes());
			}
			else
			{
				data.Add((0).GetBytes());
			}

			data.Add(value.DistortionIntensity.GetBytes());

			return data.ToArray().ToArray();
		}
	}
}
