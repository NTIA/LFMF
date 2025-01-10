using System;
using System.Runtime.InteropServices;

namespace ITS.Propagation
{
    /// <summary>
    /// The Low Frequency / Medium Frequency (LF/MF) Propagation Model
    /// </summary>
    public static partial class LFMF
    {
        #region 32-Bit P/Invoke Definitions

        [DllImport("LFMF_x86.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "LFMF")]
        private static extern int LFMF_x86(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
            double N_s, double d__km, double epsilon, double sigma, int pol, out Result result);

        #endregion

        #region 64-Bit P/Invoke Definitions

        [DllImport("LFMF_x64.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "LFMF")]
        private static extern int LFMF_x64(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
            double N_s, double d__km, double epsilon, double sigma, int pol, out Result result);

        #endregion

        private delegate int LFMF_Delegate(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
            double N_s, double d__km, double epsilon, double sigma, int pol, out Result result);

        private static LFMF_Delegate LFMF_Invoke;

        static LFMF()
        {
            if (Environment.Is64BitProcess)
                LFMF_Invoke = LFMF_x64;
            else
                LFMF_Invoke = LFMF_x86;
        }

        /// <summary>
        /// Compute the LFMF propagation prediction
        /// </summary>
        /// <param name="h_tx__meter">Transmitter height, in meters</param>
        /// <param name="h_rx__meter">Receiver height, in meters</param>
        /// <param name="f__mhz">Frequency, in MHz</param>
        /// <param name="P_tx__watt">Transmit power, in watts</param>
        /// <param name="N_s">Surface refractivity, in N-Units</param>
        /// <param name="d__km">Path distance, in km</param>
        /// <param name="epsilon">Relative permittivity</param>
        /// <param name="sigma">Conductivity</param>
        /// <param name="pol">Polarization</param>
        /// <param name="result">Prediction result</param>
        /// <returns>Error code</returns>
        public static int Invoke(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
            double N_s, double d__km, double epsilon, double sigma, Polarization pol, out Result result)
        {
            return LFMF_Invoke(h_tx__meter, h_rx__meter, f__mhz, P_tx__watt, N_s,
                d__km, epsilon, sigma, (int)pol, out result);
        }

        /// <summary>
        /// Compute the LFMF propagation prediction
        /// </summary>
        /// <param name="h_tx__meter">Transmitter height, in meters</param>
        /// <param name="h_rx__meter">Receiver height, in meters</param>
        /// <param name="f__mhz">Frequency, in MHz</param>
        /// <param name="P_tx__watt">Transmit power, in watts</param>
        /// <param name="N_s">Surface refractivity, in N-Units</param>
        /// <param name="d__km">Path distance, in km</param>
        /// <param name="epsilon">Relative permittivity</param>
        /// <param name="sigma">Conductivity</param>
        /// <param name="pol">Polarization</param>
        /// <param name="result">Prediction result</param>
        /// <returns>Error code</returns>
        public static int Invoke(double h_tx__meter, double h_rx__meter, double f__mhz, double P_tx__watt,
            double N_s, double d__km, double epsilon, double sigma, int pol, out Result result)
        {
            return LFMF_Invoke(h_tx__meter, h_rx__meter, f__mhz, P_tx__watt, N_s,
                d__km, epsilon, sigma, pol, out result);
        }
    }
}
