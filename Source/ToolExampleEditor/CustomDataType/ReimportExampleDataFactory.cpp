#include "ReimportExampleDataFactory.h"
#include "ToolExampleEditor/ToolExampleEditor.h"
#include "ExampleDataFactory.h"
#include "ToolExample/CustomDataType/ExampleData.h"

bool UReimportExampleDataFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UExampleData* ExampleData = Cast<UExampleData>(Obj);
	if (ExampleData)
	{
		OutFilenames.Add(UAssetImportData::ResolveImportFilename(ExampleData->SourceFilePath, ExampleData->GetOutermost()));
		return true;
	}
	return false;
}

void UReimportExampleDataFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	UExampleData* ExampleData = Cast<UExampleData>(Obj);
	if (ExampleData && ensure(NewReimportPaths.Num() == 1))
	{
		ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename(NewReimportPaths[0], ExampleData->GetOutermost());
	}
}

EReimportResult::Type UReimportExampleDataFactory::Reimport(UObject* Obj)
{
	UExampleData* ExampleData = Cast<UExampleData>(Obj);
	if (!ExampleData)
	{
		return EReimportResult::Failed;
	}

	const FString Filename = UAssetImportData::ResolveImportFilename(ExampleData->SourceFilePath, ExampleData->GetOutermost());
	if (!FPaths::GetExtension(Filename).Equals(TEXT("xmp")))
	{
		return EReimportResult::Failed;
	}

	CurrentFilename = Filename;
	FString Data;
	if (FFileHelper::LoadFileToString(Data, *CurrentFilename))
	{
		const TCHAR* Ptr = *Data;
		ExampleData->Modify();
		ExampleData->MarkPackageDirty();
		ExampleData->ExampleString = Ptr;
		// save the source file path and timestamp
		ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename(CurrentFilename, ExampleData->GetOutermost());
	}

	return EReimportResult::Succeeded;
}
