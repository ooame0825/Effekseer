using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Effekseer.GUI
{
    public partial class DockNodeRendererCommonValues2 : DockContent
    {
        public DockNodeRendererCommonValues2()
        {
            InitializeComponent();

            HandleCreated += new EventHandler(DockNodeRendererCommonValues2_HandleCreated);
            HandleDestroyed += new EventHandler(DockNodeRendererCommonValues2_HandleDestroyed);

            lp_RendererCommon2.SetType(typeof(Data.RendererCommonValues2));

            Icon = Icon.FromHandle(((Bitmap)Properties.Resources.IconRendererCommon).GetHicon());
        }

        void Read()
        {
            if (Core.SelectedNode != null)
            {
                if (Core.SelectedNode is Data.Node)
                {
                    lp_RendererCommon2.SetValue(((Data.Node)Core.SelectedNode).RendererCommonValues2);
                }
                else
                {
                    lp_RendererCommon2.SetValue(null);
                }
            }
            else
            {
                lp_RendererCommon2.SetValue(null);
            }
        }

        void OnAfterSelectNode(object sender, EventArgs e)
        {
            Read();
        }

        private void DockNodeRendererCommonValues2_Load(object sender, EventArgs e)
        {
           // Read();
        }

        void DockNodeRendererCommonValues2_HandleDestroyed(object sender, EventArgs e)
        {
            Core.OnAfterSelectNode -= OnAfterSelectNode;
        }

        void DockNodeRendererCommonValues2_HandleCreated(object sender, EventArgs e)
        {
            Core.OnAfterSelectNode += OnAfterSelectNode;
        }
    }
}
