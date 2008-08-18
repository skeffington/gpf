#pragma once
#include <QtCore>
#include "GpfBase.h"
#include "GpfIndexFileInfo.h"


class k_GpfIndexer
{
public:
	k_GpfIndexer(QString as_GenomeFilename, QString as_GpfIndexFilename, QString as_GenomeTitle);
	~k_GpfIndexer();

	void CompileIndex();

private:
	QFile mk_IndexFile;
	QString ms_GenomeFilename;
	QString ms_GenomeTitle;
	k_GpfBase mk_GpfBase;
	QString ms_IndexFilename;
	k_GpfIndexFileInfo mk_IndexFileInfo;

	void WriteHeader();
	void WriteGenomeTitle();
	void RecodeDna(QString as_GenomeFilename);
	void WriteScaffoldLabels();
	void TranslateDna();
	void CreateIndex();

	void get_AminoAcidCount(int ai_NucleotideCount, int& ai_Count0, int& ai_Count1, int& ai_Count2);

	template <typename T> QFile* SortEntriesOnDisk(QFile& ak_SourceFile, QFile& ak_TemporaryFile, QVector<unsigned int> ak_ChunkOffsets, unsigned int aui_EntryCount, bool (*af_LessThan_)(T*, T*), bool ab_Verbose = true);
	void WriteMassTables(QFile& ak_SourceFile, unsigned int aui_EntryCount);
	template <typename T> void Sort(T* ar_Entries_, unsigned int aui_First, unsigned int aui_Last, bool (*af_LessThan_)(T*, T*), T* ar_TempEntries_ = NULL);
};
