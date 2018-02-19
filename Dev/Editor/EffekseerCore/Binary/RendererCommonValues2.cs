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

            return data.ToArray().ToArray();
        }
    }
}
