﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Effekseer.Utl
{
	public class TextureInformation
	{
		public int Width { get; private set; }
		public int Height { get; private set; }

		public TextureInformation()
		{ 
		
		}

        public bool Load(string path)
        {

            System.IO.FileStream fs = null;
            if (!System.IO.File.Exists(path)) return false;

            try
            {
                fs = System.IO.File.Open(path, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.Read);
            }
            catch (System.IO.FileNotFoundException e)
            {
                return false;
            }

            var br = new System.IO.BinaryReader(fs);

            var buf = new byte[1024];

            // png ヘッダー部分読み込み
            if (br.Read(buf, 0, 8) != 8)
            {
                fs.Dispose();
                br.Dispose();
                return false;
            }

            // png Header 89 50 4E 47 0D 0A 1A 0A
            if (buf[0] == 0x89 &&
                buf[1] == 0x50 &&
                buf[2] == 0x4E &&
                buf[3] == 0x47 &&
                buf[4] == 0x0D &&
                buf[5] == 0x0A &&
                buf[6] == 0x1A &&
                buf[7] == 0x0A)
            {
                if (br.Read(buf, 0, 25) != 25)
                {
                    fs.Dispose();
                    br.Dispose();
                    return false;
                }

                var width = new byte[] { buf[11], buf[10], buf[9], buf[8] };
                var height = new byte[] { buf[15], buf[14], buf[13], buf[12] };
                Width = BitConverter.ToInt32(width, 0);
                Height = BitConverter.ToInt32(height, 0);
            }
            // tga か拡張子で判別
            else if (path.Contains(".tga") == true)
            {
                var width = new byte[] { buf[12], 0, 0, 0 };
                var height = new byte[] { buf[14], 0, 0, 0 };

                Width = BitConverter.ToInt32(width, 0);
                Height = BitConverter.ToInt32(height, 0);
            }
            else
            {
                // 知らない拡張子なので弾く
                fs.Dispose();
                br.Dispose();
                return false;
            }

            fs.Dispose();
            br.Dispose();
            return true;
        }
    }
}
