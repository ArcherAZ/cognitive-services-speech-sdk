//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
using System.Globalization;

namespace Microsoft.CognitiveServices.Speech
{
    /// <summary>
    /// Defines payload for Connected/Disconnected events
    /// Added in version 1.2.0.
    /// </summary>
    public sealed class ConnectionEventArgs : SessionEventArgs
    {
        internal ConnectionEventArgs(Internal.ConnectionEventArgs arg)
            : base(arg)
        {
        }
    }
}