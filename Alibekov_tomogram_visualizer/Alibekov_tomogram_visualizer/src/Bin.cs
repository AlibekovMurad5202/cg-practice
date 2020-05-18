using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Alibekov_tomogram_visualizer
{
    enum Axis { z, x, y };

    class Bin
    {
        private static int real_X, real_Y, real_Z;
        private static short[] array;

        public static int X, Y, Z;
        public static short[] data;

        public Bin() { }

        public void readBIN(string path)
        {
            if (File.Exists(path))
            {
                BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open));
                
                X = reader.ReadInt32();
                Y = reader.ReadInt32();
                Z = reader.ReadInt32();

                real_X = X;
                real_Y = Y;
                real_Z = Z;

                int arraySize = X * Y * Z;
                array = new short[arraySize];
                data  = new short[arraySize];

                for (int i = 0; i < arraySize; i++)
                {
                    array[i] = reader.ReadInt16();
                    data[i]  = array[i];
                }
            }
        }

        public void change_axis(Axis axis)
        {
            data = new short[real_X * real_Y * real_Z];
            for (int k = 0; k < real_Z; k++)
                for (int j = 0; j < real_Y; j++)
                    for (int i = 0; i < real_X; i++)
                    {
                        if (axis == Axis.z)
                        {
                            data[k * real_Y * real_X + j * real_X + i] = 
                                array[k * real_Y * real_X + j * real_X + i];
                        }
                        else if (axis == Axis.x)
                        {
                            data[j * real_Z * real_X + k * real_X + i] = 
                                array[k * real_Y * real_X + j * real_X + i];
                        }
                        else
                        {
                            data[i * real_Z * real_Y + k * real_Y + j] = 
                                array[k * real_Y * real_X + j * real_X + i];
                        }

                    }
            if (axis == Axis.z)
            {
                X = real_X;
                Y = real_Y;
                Z = real_Z;
            }
            else if (axis == Axis.x)
            {
                X = real_Y;
                Y = real_Z;
                Z = real_X;
            }
            else
            {
                X = real_Y;
                Y = real_Z;
                Z = real_X;
            }
        }
    }
}
