function [Jul1,Jul2]=TT2UTC(Jul1,Jul2)
%TT2UTC   Convert from terrestrial time (TT) given as a two-part Julian
%         date to universal coordinated time (UTC) given as a two-part
%         pseudo-Julian date.
%
%INPUTS: Jul1, Jul2  Two parts of a Julian date given in TT. The units
%                    of the date are days. The full date is the sum of both
%                    terms. The date is broken into two parts to provide
%                    more bits of precision. It does not matter how the
%                    date is split.
%
%OUTPUTS: Jul1, Jul2 The time as a pseudo-Julian date in UTC.
%
%The UTC date is only pseudo-Julian, because there is not a fixed number
%of seconds in a Julian day. The convention used in the IAU standard is
%that the Julian day matches the UTC day regardless of whether the UTC day
%is 86399, 86400 or 86401 SI seconds (depending on the presence of leap
%seconds).
%
%This just calls a number of intermediate conversion functions out of the
%International Astronomical Union's (IAU) Standard's of Fundamental
%Astronomy library.
%
%October 2013 David F. Crouse, Naval Research Laboratory, Washington D.C.
%(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.

[Jul1,Jul2]=TT2TAI(Jul1,Jul2);
[Jul1,Jul2]=TAI2UTC(Jul1,Jul2);
end

%LICENSE:
%
%The source code is in the public domain and not licensed or under
%copyright. The information and software may be used freely by the public.
%As required by 17 U.S.C. 403, third parties producing copyrighted works
%consisting predominantly of the material produced by U.S. government
%agencies must provide notice with such work(s) identifying the U.S.
%Government material incorporated and stating that such material is not
%subject to copyright protection.
%
%Derived works shall not identify themselves in a manner that implies an
%endorsement by or an affiliation with the Naval Research Laboratory.
%
%RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF THE
%SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY THE NAVAL
%RESEARCH LABORATORY FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE ACTIONS
%OF RECIPIENT IN THE USE OF THE SOFTWARE.
