using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RCWS_Situation_room
{
    internal class OpenCV
    {
        IplImage bin;
        IplImage con;
        IplImage mom;


        public IplImage Binary(IplImage src)
        {
            bin = new IplImage(src.Size, BitDepth.U8, 1);
            Cv.CvtColor(src, bin, ColorConversion.RgbToGray);
            Cv.Threshold(bin, bin, 150, 255, ThresholdType.Binary);
            return bin;
        }

        public IplImage Contour(IplImage src)
        {
            con = new IplImage(src.Size, BitDepth.U8, 3);
            bin = new IplImage(src.Size, BitDepth.U8, 1);

            Cv.Copy(src, con);
            bin = this.Binary(src);

            CvMemStorage Storage = new CvMemStorage();
            CvSeq<CvPoint> contours;

            CvContourScanner scanner = Cv.StartFindContours(bin, Storage, CvContour.SizeOf, ContourRetrieval.List, ContourChain.ApproxNone);

            // #1        
            while (true)
            {
                contours = Cv.FindNextContour(scanner);

                if (contours == null) break;
                else
                {
                    double area = Cv.ContourArea(contours);
                    if (area > 1000) continue;
                    //Cv.DrawContours(con, contours, CvColor.Yellow, CvColor.Red, 1, 4, LineType.AntiAlias);
                    CvSeq<CvPoint> approx = Cv.ApproxPoly(contours, CvContour.SizeOf, Storage, ApproxPolyMethod.DP, contours.ContourPerimeter() * 0.02, false);
                    //double area = Cv.ContourArea(contours);
                    CvRect rect = Cv.BoundingRect(contours);
                    double radius = rect.Width / 2;

                    if (Math.Abs(1 - ((double)rect.Width / rect.Height)) <= 0.2 && Math.Abs(1 - (area / (Math.PI * Math.Pow(radius, 2)))) <= 0.2)
                    {
                        Cv.DrawContours(con, contours, CvColor.Yellow, CvColor.Red, 1, 4, LineType.AntiAlias);
                    }
                }
            }
            Cv.EndFindContours(scanner);

            // #2        
            //foreach (CvSeq<CvPoint> c in scanner)
            //{
            //    con.DrawContours(c, CvColor.Yellow, CvColor.Red, 1, 4, LineType.AntiAlias);
            //}
            //Cv.ClearSeq(contours);

            Cv.ReleaseMemStorage(Storage);

            return con;
        }

        public Tuple<IplImage, int, int> Moment(IplImage src)
        {
            mom = new IplImage(src.Size, BitDepth.U8, 3);
            bin = new IplImage(src.Size, BitDepth.U8, 1);

            Cv.Copy(src, mom);
            bin = this.Binary(src);

            CvMemStorage Storage = new CvMemStorage();
            CvSeq<CvPoint> contours;
            Cv.FindContours(bin, Storage, out contours, CvContour.SizeOf, ContourRetrieval.List, ContourChain.ApproxNone);

            CvSeq<CvPoint> apcon_seq = Cv.ApproxPoly(contours, CvContour.SizeOf, Storage, ApproxPolyMethod.DP, 3, true);

            CvMoments moments;
            int cX = 0, cY = 0;

            for (CvSeq<CvPoint> c = apcon_seq; c != null; c = c.HNext)
            {
                double area = Cv.ContourArea(c);
                if (area < 1000)
                {
                    continue;
                }

                if (c.Total > 4)
                {
                    Cv.Moments(c, out moments, true);

                    cX = Convert.ToInt32(moments.M10 / moments.M00);
                    cY = Convert.ToInt32(moments.M01 / moments.M00);

                    Cv.Circle(mom, new CvPoint(cX, cY), 5, CvColor.Red, -1);
                }
            }
            return new Tuple<IplImage, int, int>(mom, cX, cY);
        }
        public void Dispose()
        {
            if (bin != null) Cv.ReleaseImage(bin);
            if (mom != null) Cv.ReleaseImage(con);
            if (mom != null) Cv.ReleaseImage(mom);
        }
    }
}
