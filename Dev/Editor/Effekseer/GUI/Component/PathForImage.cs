using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace Effekseer.GUI.Component
{
	public partial class PathForImage : UserControl
	{
		public PathForImage()
		{
			InitializeComponent();

			EnableUndo = true;

			this.SuspendLayout();
			Anchor = AnchorStyles.Left | AnchorStyles.Right;
			this.ResumeLayout(false);

			Read();

			HandleDestroyed += new EventHandler(Path_HandleDestroyed);
			Core.OnAfterNew += Core_OnAfterNew;
			Core.OnAfterSave += Core_OnAfterSave;
			Core.OnAfterLoad += Core_OnAfterLoad;
			Core.OnReload += Core_OnReload;
		}

		Data.Value.Path binding = null;

		public bool EnableUndo { get; set; }

		public Data.Value.Path Binding
		{
			get
			{
				return binding;
			}
			set
			{
				if (binding == value) return;

				if (binding != null)
				{
					
				}

				binding = value;

				if (binding != null)
				{
					
				}

				Read();
			}
		}

		public void SetBinding(object o)
		{
			var o_ = o as Data.Value.Path;
			Binding = o_;
		}

		void Read()
		{
			if (binding != null)
			{
				btn_load.Enabled = true;
				lbl_file.Text = binding.GetRelativePath();
                tooltip_file.SetToolTip(lbl_file, lbl_file.Text);
				if (lbl_file.Text.Length > 0)
				{
					UpdatePreview(binding.GetAbsolutePath());
				}
				else
				{
					//this.Height = 20;
				}
			}
			else
			{
				btn_load.Enabled = false;
				lbl_file.Text = string.Empty;
				lbl_info.Text = string.Empty;
				pic_preview.Image = null;
			}
		}

        void UpdatePreview(string path)
        {
            if (!System.IO.File.Exists(path))
            {
                return;
            }

            try
            {
                // ミニ窓用のデータ読み込み
                // 拡張子で png 判定
                if (binding.GetAbsolutePath().Contains(".png") == true)
                {
                    Bitmap srcbmp = new Bitmap(binding.GetAbsolutePath());
                    lbl_info.Text = "" + srcbmp.Width + "x" + srcbmp.Height + " " + srcbmp.PixelFormat.ToString();

                    int height = (128 <= srcbmp.Height) ? 128 : srcbmp.Height;
                    int width = srcbmp.Width * height / srcbmp.Height;
                    Bitmap dstbmp = new Bitmap(width, height);
                    Graphics g = Graphics.FromImage(dstbmp);
                    // 市松模様を描画
                    for (int i = 0; i < height / 16; i++)
                    {
                        for (int j = 0; j < width / 16; j++)
                        {
                            g.FillRectangle(Brushes.White, j * 16, i * 16, 8, 8);
                            g.FillRectangle(Brushes.LightGray, j * 16, i * 16 + 8, 8, 8);
                            g.FillRectangle(Brushes.LightGray, j * 16 + 8, i * 16, 8, 8);
                            g.FillRectangle(Brushes.White, j * 16 + 8, i * 16 + 8, 8, 8);
                        }
                    }
                    // 画像を描画
                    g.DrawImage(srcbmp, 0, 0, width, height);
                    g.Dispose();

                    pic_preview.Width = width;
                    pic_preview.Height = height;
                    pic_preview.Image = dstbmp;
                    srcbmp.Dispose();

                    //this.Height = 40 + height;
                }
                // 拡張子で tga 判定
                else if (binding.GetAbsolutePath().Contains(".tga") == true)
                {
                    // ファイルを開いてバイナリで読み込み
                    System.IO.FileStream fs = null;

                    fs = System.IO.File.Open(
                        binding.GetAbsolutePath(),
                        System.IO.FileMode.Open,
                        System.IO.FileAccess.Read,
                        System.IO.FileShare.Read);

                    var br = new System.IO.BinaryReader(fs);

                    // ヘッダー部読み込み
                    var header = new byte[18];
                    br.Read(header, 0, 18);

                    // 画像の大きさ取得
                    int width = header[12] + header[13] * 256;
                    int height = header[14] + header[15] * 256;

                    // 格納されているカラーデータのサイズ
                    int color_size = (width * height) * 4;

                    // バイナリからカラーデータ読み込み
                    byte[] pixel_data = new byte[color_size];
                    br.Read(pixel_data, 0, color_size);

                    // もう使わないので削除
                    fs.Dispose();
                    br.Dispose();

                    // Bitmap 作成
                    Bitmap bmp = new Bitmap(width, height);

                    // ピクセル単位で読み込み
                    for (int y = 0; y < height; y++)
                    {
                        for (int x = 0; x < width; x++)
                        {
                            int by = y * width * 4;
                            int bx = x * 4;

                            int base_i = by + bx;

                            Color color =
                                Color.FromArgb(
                                    pixel_data[base_i + 3],
                                    pixel_data[base_i + 2],
                                    pixel_data[base_i + 1],
                                    pixel_data[base_i + 0]
                                    );

                            bmp.SetPixel(x, (height - 1) - y, color);
                        }
                    }

                    // プレビュー用データを設定
                    lbl_info.Text = "" + bmp.Width + "x" + bmp.Height + " " + bmp.PixelFormat.ToString();
                    pic_preview.Width = width;
                    pic_preview.Height = height;
                    pic_preview.Image = bmp;
                }
            }
            catch (Exception e)
            {
                if (path == null) path = string.Empty;
                System.IO.File.WriteAllText("error_image.txt", path + "\n" + e.ToString());
                pic_preview.Image = null;
            }
        }

        private void btn_load_Click(object sender, EventArgs e)
		{
			if (binding == null) return;

			OpenFileDialog ofd = new OpenFileDialog();

			ofd.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
			ofd.Filter = binding.Filter;
			ofd.FilterIndex = 2;
			ofd.Multiselect = false;

			if (ofd.ShowDialog() == DialogResult.OK)
			{
				var filepath = ofd.FileName;
				binding.SetAbsolutePath(filepath);

				System.IO.Directory.SetCurrentDirectory(System.IO.Path.GetDirectoryName(filepath));
			}
			else
			{
				return;
			}

			Read();
		}

		private void btn_delete_Click(object sender, EventArgs e)
		{
			binding.SetAbsolutePath("");
			Read();
		}

		void Core_OnAfterLoad(object sender, EventArgs e)
		{
			Read();
		}

		void Core_OnAfterSave(object sender, EventArgs e)
		{
			Read();
		}

		void Core_OnAfterNew(object sender, EventArgs e)
		{
			Read();
		}

		void Core_OnReload(object sender, EventArgs e)
		{
			Read();
		}

		void Path_HandleDestroyed(object sender, EventArgs e)
		{
			Binding = null;
			Core.OnAfterNew -= Core_OnAfterNew;
			Core.OnAfterSave -= Core_OnAfterSave;
			Core.OnAfterLoad -= Core_OnAfterLoad;
		}
		
		private bool CheckExtension(string path)
		{
			Match match = Regex.Match(binding.Filter, "\\*(\\.[a-zA-Z0-9]*)");
			string extension = match.Value.Substring(1);
			return System.IO.Path.GetExtension(path) == extension;
		}

		private string GetDragFile(DragEventArgs e)
		{
			{	// FileViewerからのDrag
				var fileItem = e.Data.GetData(typeof(DockFileViewer.FileItem)) as DockFileViewer.FileItem;
				if (fileItem != null) {
					return fileItem.FilePath;
				}
			}

			{	// ExplorerからのDrag
				var dropFiles = (string[])e.Data.GetData(DataFormats.FileDrop);
				if (dropFiles != null && dropFiles.Length == 1) {
					return dropFiles[0];
				}
			}
			return null;
		}

		private void PathForImage_DragEnter(object sender, DragEventArgs e)
		{
			string filePath = GetDragFile(e);

			if (filePath != null) {
				if (CheckExtension(filePath)) {
					e.Effect = DragDropEffects.Link;
				}
			}
		}

		private void PathForImage_DragLeave(object sender, EventArgs e)
		{
		}

		private void PathForImage_DragDrop(object sender, DragEventArgs e)
		{
			string filePath = GetDragFile(e);
			
			if (filePath != null) {
				if (CheckExtension(filePath)) {
					binding.SetAbsolutePath(filePath);
					Read();
				}
			}
		}
	}
}
