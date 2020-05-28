using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Alibekov_tomogram_visualizer
{
    public partial class Form1 : Form
    {
        enum visualizationType
        {
            Quads = 0,
            QuadStrip,
            Texture
        }

        Bin file = new Bin();
        View view = new View();
        bool loaded = false;
        bool needReload = false;
        string fileName = "";
        string loadedFileName = "";
        int currentLayer;

        int FrameCount;
        DateTime NextFPSUpdate = DateTime.Now.AddSeconds(1);
        void displayFPS()
        {
            if ((DateTime.Now >= NextFPSUpdate) && (loaded))
            {
                label2.Text = String.Format("FPS: {0}", FrameCount);
                NextFPSUpdate = DateTime.Now.AddSeconds(1);
                FrameCount = 0;
            }
            FrameCount++;
        }

        public Form1()
        {
            InitializeComponent();

            textBox1.Text = "C:/TV/Alibekov_tomogram_visualizer/Alibekov_tomogram_visualizer/Resources/testdata.bin";
            loaded = false;
            trackBar1.Minimum = 0;
            trackBar1.Maximum = Bin.Z - 1;
            label2.Text = "FPS: 0";
        }

        void Application_Idle(object sender, EventArgs e)
        {
            while (glControl1.IsIdle)
            {
                displayFPS();
                glControl1.Invalidate();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                if (fileName == dialog.FileName)
                    MessageBox.Show("");
                fileName = dialog.FileName;
                textBox1.Text = fileName;
                file.readBIN(fileName);
                view.SetupView(glControl1.Width, glControl1.Height);
                loaded = true;
                loadedFileName = fileName;
                glControl1.Invalidate();
                trackBar1.Minimum = 0;
                trackBar1.Maximum = Bin.Z - 1;
                comboBox1.SelectedIndex = 0;
                comboBox2.SelectedIndex = 0;
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            currentLayer = trackBar1.Value;
            needReload = true;
            glControl1.Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (fileName == loadedFileName)
                MessageBox.Show("This file has already been loaded",
                                "Loading file",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Warning,
                                MessageBoxDefaultButton.Button1);
            else
            {
                file.readBIN(fileName);
                view.SetupView(glControl1.Width, glControl1.Height);
                loaded = true;
                loadedFileName = fileName;
                glControl1.Invalidate();
                trackBar1.Minimum = 0;
                trackBar1.Maximum = Bin.Z - 1;
                comboBox1.SelectedIndex = 0;
                comboBox2.SelectedIndex = 0;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Application.Idle += Application_Idle;
        }

        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            if (loaded)
            {
                switch (comboBox1.SelectedIndex)
                {
                    case (int)visualizationType.Quads:
                        view.DrawQuads(currentLayer);
                        break;
                    case (int)visualizationType.Texture:
                        if (needReload)
                        {
                            view.generateTextureImage(currentLayer);
                            view.Load2DTexture();
                            needReload = false;
                        }
                        view.DrawTexture();
                        break;
                    case (int)visualizationType.QuadStrip:
                        view.DrawQuadStrip(currentLayer);
                        break;
                }
                glControl1.SwapBuffers();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            fileName = textBox1.Text;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            needReload = true;
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            view.setMin(trackBar2.Value * 100);
            label5.Text = String.Format("TF_min: {0}", trackBar2.Value * 100);
            needReload = true;
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            view.setWidth(trackBar3.Value * 50);
            label6.Text = String.Format("TF_width: {0}", trackBar3.Value * 50);
            needReload = true;
        }

        private void Form1_ResizeEnd(object sender, EventArgs e)
        {
            view.SetupView(glControl1.Width, glControl1.Height);
            glControl1.Invalidate();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            trackBar1.Value = trackBar1.Minimum;
            currentLayer = trackBar1.Value;
            if (loaded)
            {
                Axis current_axis = Axis.z;
                switch (comboBox2.SelectedIndex)
                {
                    case 0: current_axis = Axis.z;
                        break;
                    case 1: current_axis = Axis.x;
                        break;
                    case 2: current_axis = Axis.y;
                        break;
                }
                
                file.change_axis(current_axis);
                view.SetupView(glControl1.Width, glControl1.Height);
                glControl1.Invalidate();
                needReload = true;
                trackBar1.Minimum = 0;
                trackBar1.Maximum = Bin.Z - 1;
            }
        }
    }
}
