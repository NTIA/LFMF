using System;
using System.Runtime.InteropServices;

namespace ITS.Propagation
{
    public static partial class LFMF
    {
        /// <summary>
        /// Polarization
        /// </summary>
        public enum Polarization : int
        {
            /// <summary>
            /// Horizontal polarization
            /// </summary>
            Horizontal = 0,

            /// <summary>
            /// Vertical polarization
            /// </summary>
            Vertical = 1
        }

        /// <summary>
        /// Solution method used
        /// </summary>
        public enum Method : int
        {
            /// <summary>
            /// Flat earth with curve correction
            /// </summary>
            FlatEarthCurveCorrection = 0,

            /// <summary>
            /// Residue series
            /// </summary>
            ResidueSeries = 1
        }

        /// <summary>
        /// LF/MF prediction results
        /// </summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct Result
        {
            /// <summary>
            /// Basic transmission loss, in dB
            /// </summary>
            public double A_btl__db;

            /// <summary>
            /// Electic field strength, in db(uV/m)
            /// </summary>
            public double E_dBuVm;

            /// <summary>
            /// Received power, in dBm
            /// </summary>
            public double P_rx__dbm;

            /// <summary>
            /// Solution method used
            /// </summary>
            public Method Method;
        }
    }
}
