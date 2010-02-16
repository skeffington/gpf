/*
Copyright (c) 2007-2008 Michael Specht

This file is part of GPF.

GPF is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GPF is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GPF.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <QtCore>
#include "RefPtr.h"


class k_GpfIndexFile;

struct r_SearchIntronSplitAlignments
{
    enum Enumeration
    {
        Yes,
        No,
        Conditional
    };
};

struct r_IntronSearchType
{
    enum Enumeration
    {
        Exhaustive,
        Quick
    };
};


class k_GpfQuery
{
public:
	k_GpfQuery(k_GpfIndexFile& ak_GpfIndexFile, double ad_MassAccuracy,
               bool ab_SimilaritySearch, bool ab_DistinguishIL,
               bool ab_SearchImmediate, r_SearchIntronSplitAlignments::Enumeration 
               ae_SearchIntronSplitAlignments, r_IntronSearchType::Enumeration
               ae_IntronSearchType, int ai_MaxIntronLength, 
               QString as_IntronSpliceSites, bool ab_Quiet, 
               QIODevice* ak_Output_);
	virtual ~k_GpfQuery();
	
	void execute(const QString& as_Peptide);
    void execute(const QStringList ak_Peptides);
	
protected:
    int reverseSpliceSequence(int ai_Sequence, int ai_Length);
    
    k_GpfIndexFile& mk_GpfIndexFile;
	double md_MassAccuracy;
    bool mb_SimilaritySearch;
    bool mb_DistinguishIL;
    bool mb_SearchImmediateAlignments;
    r_SearchIntronSplitAlignments::Enumeration me_SearchIntronSplitAlignments;
    r_IntronSearchType::Enumeration me_IntronSearchType;
	int mi_MinIntronLength;
	int mi_MaxIntronLength;
    int mi_MinExonLength;
    QString ms_IntronSpliceSites;
    bool mb_Quiet;
    QIODevice* mk_Output_;
	
	typedef QPair<int, int> tk_IntPair;
    typedef QPair<qint64, qint64> tk_QInt64Pair;
    typedef QHash<tk_IntPair, QList<tk_IntPair> > tk_IntPairListHash;

	// GT/2: [AG/2]
	// GC/2: [AG/2]
	tk_IntPairListHash mk_IntronNTerm;
	
	// AG/2: [GT/2, GC/2]
	tk_IntPairListHash mk_IntronCTerm;
    
    // TG/2: [GA/2]
    // CG/2: [GA/2]
    tk_IntPairListHash mk_IntronNTermReverse;
    
    // GA/2: [TG/2, CG/2]
    tk_IntPairListHash mk_IntronCTermReverse;
    
	int mi_IntronNTermMaxLength;
	int mi_IntronCTermMaxLength;
};
