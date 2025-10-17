#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
bool isLE = false;
uint32_t evp1Address = 0;
#pragma pack(push, 1)
struct BDLHeader {
    char magic[4];     
    char fileType[4];   
    uint32_t fileSize;
    uint32_t numSections;
    uint32_t sectionOffset;
    uint32_t unknown;
};
struct INF1 {
    char magic[4];        
    uint32_t size;
    uint16_t unknown1;
    uint16_t matrixGroupCount;
    uint32_t vertexCount;
    uint32_t sceneHierarchyOffset;
    uint32_t sceneHierarchyOffset2;
};

struct INF1Node {
    uint16_t type;
    uint16_t unknown;
};

struct VTX1Header {
    char     magic[4];          
    uint32_t size;
    uint32_t vertexFormatOffset;
    uint32_t posDataOffset;
    uint32_t nrmDataOffset;
    uint32_t nbtDataOffset;
    uint32_t colDataOffset[2];
    uint32_t texDataOffset[8];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct VTX1ArrayFormat {
    uint32_t attributeType;
    uint32_t componentCount;
    uint32_t dataType;
    uint8_t  shift;
    uint8_t  pad[3];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct EVP1Header {
    char     magic[4];
    uint32_t size;
    uint16_t matrixCount;
    uint16_t padding;
    uint32_t jointCountOffset;
    uint32_t indexTableOffset;
    uint32_t weightTableOffset;
    uint32_t inverseBindOffset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DRW1Header {
    char     magic[4];
    uint32_t size;
    uint16_t elementCount;
    uint16_t padding;
    uint32_t matrixTypeArrayOffset;
    uint32_t dataArrayOffset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct JNT1Header {
    char magic[4];             
    uint32_t size;               
    uint16_t jointCount;        
    uint16_t padding;           
    uint32_t transformTableOffset;
    uint32_t remapTableOffset;
    uint32_t nameTableOffset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHP1Header {
    char     magic[4];               
    uint32_t chunkSize;             
    uint16_t sectionCount;         
    uint16_t padding;           
    uint32_t shapeDataOffset;      
    uint32_t remapTableOffset;      
    uint32_t nameTableOffset;       
    uint32_t attributeTableOffset;  
    uint32_t matrixTableOffset;     
    uint32_t primitiveDataOffset;   
    uint32_t matrixDataOffset;      
    uint32_t matrixGroupTableOffset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ShapeData {
    uint8_t  matrixType;
    uint8_t  padding1;
    uint16_t matrixGroupCount;
    uint16_t attributesOffset;
    uint16_t firstMatrixDataIndex;
    uint16_t firstMatrixGroupIndex;
    uint16_t padding2;
    uint32_t boundingBoxMinX;
    uint32_t boundingBoxMinY;
    uint32_t boundingBoxMinZ;
    uint32_t boundingBoxMaxX;
    uint32_t boundingBoxMaxY;
    uint32_t boundingBoxMaxZ;
    uint32_t boundingBoxMaxZ2;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct MatrixData {
    int16_t useMtxIndex;      
    int16_t useMtxCount;      
    int32_t firstUseMtxIndex;  
};
#pragma pack(pop)
#pragma pack(push, 1)
struct MAT3Header {
    char     magic[4];      
    uint32_t sectionSize;   
    uint16_t materialCount;    
    uint16_t padding1;    

    uint32_t materialEntryOffset;   
    uint32_t remapTableOffset;    
    uint32_t stringTableOffset;   
    uint32_t indirectInfoOffset;    
    uint32_t cullModeOffset;        
    uint32_t materialColorOffset;     
    uint32_t numColorChannelsOffset;  
    uint32_t colorChannelInfoOffset;   
    uint32_t ambientColorOffset;      
    uint32_t lightInfoOffset;       
    uint32_t numTexGensOffset;    
    uint32_t texGenInfoOffset;     
    uint32_t postTexGenInfoOffset;  
    uint32_t texMatrixOffset;      
    uint32_t postTexMatrixOffset;
    uint32_t textureRemapTableOffset; 
    uint32_t tevOrderInfoOffset;  
    uint32_t tevColorOffset;     
    uint32_t tevKonstColorOffset;  
    uint32_t numTevStagesOffset; 
    uint32_t tevStageInfoOffset;
    uint32_t tevSwapModeInfoOffset;
    uint32_t tevSwapModeTableOffset; 
    uint32_t fogInfoOffset; 
    uint32_t alphaCompareOffset; 
    uint32_t blendModeOffset;  
    uint32_t zModeOffset; 
    uint32_t zCompareOffset; 
    uint32_t ditherOffset;
    uint32_t nbtScaleOffset;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct IndirectStage {
    uint8_t indStage;   
    uint8_t texCoordId;    
    uint8_t texMap;     
    uint8_t scaleS;       
    uint8_t scaleT;     
    uint8_t pad[3];       
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TevStage {
    uint8_t tevStage;
    uint8_t colorIn[4];
    uint8_t colorOp;
    uint8_t colorBias;
    uint8_t colorScale;
    uint8_t colorClamp;
    uint8_t colorRegId;

    uint8_t alphaIn[4];
    uint8_t alphaOp;
    uint8_t alphaBias;
    uint8_t alphaScale;
    uint8_t alphaClamp;
    uint8_t alphaRegId;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BlendMode {
    uint8_t type;
    uint8_t sourceFactor;
    uint8_t destinationFactor;
    uint8_t logicOp;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct MDL3Header {
    char     magic[4];         
    uint32_t sectionSize;          
    uint16_t entryCount;           
    uint16_t padding;              

    uint32_t packetOffset;         
    uint32_t subPacketLocationOffset;
    uint32_t matrixIndexOffset;  
    uint32_t pixelEngineModesOffset;
    uint32_t indexesOffset;   
    uint32_t stringTableOffset;  
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEX1Header {
    char     magic[4];           
    uint32_t sectionSize;        
    uint16_t textureCount;         
    uint16_t padding;             
    uint32_t textureHeaderOffset;   
    uint32_t stringTableOffset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TextureHeader {
    uint16_t imageOffset;  
    uint16_t width;       
    uint16_t height;      
    uint16_t format;         


    uint16_t  minFilter;      
    uint16_t  magFilter;
    uint32_t    lodBias;      

    uint32_t  edgeLODEnable;  
    uint32_t  minLOD;
    uint32_t  maxLOD;
    uint32_t  unpacked;     
};
#pragma pack(pop)

uint32_t Swap32(uint32_t val) {
    return ((val >> 24) & 0x000000FF) |
           ((val >> 8)  & 0x0000FF00) |
           ((val << 8)  & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}
uint16_t Swap16(uint16_t val) {
    return (val >> 8) | (val << 8);
}
void ConvertHeaderEndian(BDLHeader& header) {
    std::reverse(header.magic, header.magic + 4);
    std::reverse(header.fileType, header.fileType + 4);
    header.fileSize = Swap32(header.fileSize);
    header.numSections = Swap32(header.numSections);
    header.unknown = Swap32(header.unknown);
}
uint32_t ConvertINF1(std::ifstream& in, std::ofstream& out) {
    INF1 inf1;
    in.read(reinterpret_cast<char*>(&inf1), sizeof(inf1));

    std::reverse(inf1.magic, inf1.magic + 4);
    inf1.size = Swap32(inf1.size);
    inf1.unknown1 = Swap16(inf1.unknown1);
    inf1.matrixGroupCount = Swap16(inf1.matrixGroupCount);
    inf1.vertexCount = Swap32(inf1.vertexCount);
    inf1.sceneHierarchyOffset = Swap32(inf1.sceneHierarchyOffset);
    inf1.sceneHierarchyOffset2 = Swap32(inf1.sceneHierarchyOffset2);

    out.write(reinterpret_cast<char*>(&inf1), sizeof(inf1));

if (isLE == false)
{
    size_t nodeCount = (inf1.size - sizeof(INF1)) / sizeof(INF1Node);
    for (size_t i = 0; i < nodeCount; i++) {
        
        INF1Node node;
        in.read(reinterpret_cast<char*>(&node), sizeof(node));
        node.type = Swap16(node.type);
        node.unknown = Swap16(node.unknown);
        out.write(reinterpret_cast<char*>(&node), sizeof(node));
    }
}
else
{
    size_t nodeCount = (Swap32(inf1.size) - sizeof(INF1)) / sizeof(INF1Node);
    for (size_t i = 0; i < nodeCount; i++) {
        
        INF1Node node;
        in.read(reinterpret_cast<char*>(&node), sizeof(node));
        node.type = Swap16(node.type);
        node.unknown = Swap16(node.unknown);
        out.write(reinterpret_cast<char*>(&node), sizeof(node));
    }
}
    return 0;
}

void ConvertAttributeTable(std::ifstream& in, std::ofstream& out, uint32_t start, uint32_t end) {
    in.seekg(start, std::ios::beg);
    while (static_cast<uint32_t>(in.tellg()) < end) {
        VTX1ArrayFormat fmt;
        in.read(reinterpret_cast<char*>(&fmt), sizeof(fmt));
        fmt.attributeType   = Swap32(fmt.attributeType);
        fmt.componentCount  = Swap32(fmt.componentCount);
        fmt.dataType        = Swap32(fmt.dataType);
        out.write(reinterpret_cast<char*>(&fmt), sizeof(fmt));
    }
}

void ConvertRaw32Block(std::ifstream& in, std::ofstream& out, uint32_t offset, uint32_t endOffset) {
    in.seekg(offset);
    out.seekp(offset);

    uint32_t count = (endOffset - offset) / 4;
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t value;
        in.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
        value = Swap32(value);
        out.write(reinterpret_cast<char*>(&value), sizeof(uint32_t));
    }
}

void ConvertVertexData(std::ifstream& in, std::ofstream& out, std::vector<uint32_t> offsets, uint32_t base, uint32_t end) {
    offsets.erase(std::remove_if(offsets.begin(), offsets.end(), [](uint32_t off) { return off == 0; }), offsets.end());
    std::sort(offsets.begin(), offsets.end());

    std::vector<std::pair<uint32_t, uint32_t>> ranges;
    for (size_t i = 0; i < offsets.size(); ++i) {
        uint32_t start = base + offsets[i];
        uint32_t next  = (i + 1 < offsets.size()) ? base + offsets[i + 1] : end;
        if (start >= next) continue;
        ranges.emplace_back(start, next);
    }

    for (auto [start, stop] : ranges) {
        in.seekg(start, std::ios::beg);
        for (uint32_t pos = start; pos < stop; pos += 2) {
            uint16_t val;
            in.read(reinterpret_cast<char*>(&val), 2);
            val = Swap16(val);
            out.write(reinterpret_cast<char*>(&val), 2);
        }
    }
}

void CopyColorData(std::ifstream& in, std::ofstream& out, uint32_t base, uint32_t sectionEnd, const uint32_t colOffsets[2]) {
    for (int i = 0; i < 2; ++i) {
        if (colOffsets[i] != 0) {
            uint32_t start = base + colOffsets[i];

out.seekp(start, std::ios::beg);


            in.seekg(start, std::ios::beg);
            uint32_t end = sectionEnd;
            std::vector<char> buffer(sectionEnd - start);
            in.read(buffer.data(), buffer.size());
            out.write(buffer.data(), buffer.size());
            
        }
    }
}

void CopyColorDataLE(std::ifstream& in, std::ofstream& out, uint32_t base, uint32_t sectionEnd, const uint32_t colOffsets[2]) {
    for (int i = 0; i < 2; ++i) {
        if (Swap32(colOffsets[i]) != 0) {
            uint32_t start = base + Swap32(colOffsets[i]);

out.seekp(start, std::ios::beg);


            in.seekg(start, std::ios::beg);
            uint32_t end = sectionEnd;
            std::vector<char> buffer(sectionEnd - start);
            in.read(buffer.data(), buffer.size());
            out.write(buffer.data(), buffer.size());
            
        }
    }
}


void ConvertTexDataSections(std::ifstream& in, std::ofstream& out, const VTX1Header& vtx1, uint32_t base, uint32_t sectionEnd) {
    for (int i = 0; i < 8; ++i) {
        if (vtx1.texDataOffset[i] == 0)
            continue;

        uint32_t start = base + vtx1.texDataOffset[i];

        uint32_t stop = sectionEnd;
        for (int j = i + 1; j < 8; ++j) {
            if (vtx1.texDataOffset[j] != 0) {
                stop = std::min(stop, base + vtx1.texDataOffset[j]);
                break;
            }
        }

        for (uint32_t pos = start; pos < stop; pos += 2) {
            in.seekg(pos, std::ios::beg);
            uint16_t val;
            in.read(reinterpret_cast<char*>(&val), 2);
            uint16_t swapped = Swap16(val);

            out.seekp(pos, std::ios::beg);
            out.write(reinterpret_cast<char*>(&swapped), 2);
        }
    }
}

void ConvertTexDataSectionsLE(std::ifstream& in, std::ofstream& out, const VTX1Header& vtx1, uint32_t base, uint32_t sectionEnd) {
    for (int i = 0; i < 8; ++i) {
        if (Swap32(vtx1.texDataOffset[i]) == 0)
            continue;

        uint32_t start = base + Swap32(vtx1.texDataOffset[i]);

        uint32_t stop = sectionEnd;
        for (int j = i + 1; j < 8; ++j) {
            if (Swap32(vtx1.texDataOffset[j]) != 0) {
                stop = std::min(stop, base + Swap32(vtx1.texDataOffset[j]));
                break;
            }
        }

        for (uint32_t pos = start; pos < stop; pos += 2) {
            in.seekg(pos, std::ios::beg);
            uint16_t val;
            in.read(reinterpret_cast<char*>(&val), 2);
            uint16_t swapped = Swap16(val);

            out.seekp(pos, std::ios::beg);
            out.write(reinterpret_cast<char*>(&swapped), 2);
        }
    }
}

void ConvertVTX1(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());
    VTX1Header vtx1;
    in.read(reinterpret_cast<char*>(&vtx1), sizeof(vtx1));

    std::reverse(vtx1.magic, vtx1.magic + 4);
    vtx1.size               = Swap32(vtx1.size);
    vtx1.vertexFormatOffset = Swap32(vtx1.vertexFormatOffset);
    vtx1.posDataOffset      = Swap32(vtx1.posDataOffset);
    vtx1.nrmDataOffset      = Swap32(vtx1.nrmDataOffset);
    vtx1.nbtDataOffset      = Swap32(vtx1.nbtDataOffset);
    vtx1.colDataOffset[0]   = Swap32(vtx1.colDataOffset[0]);
    vtx1.colDataOffset[1]   = Swap32(vtx1.colDataOffset[1]);
    for (int i = 0; i < 8; ++i)
        vtx1.texDataOffset[i] = Swap32(vtx1.texDataOffset[i]);
    out.write(reinterpret_cast<char*>(&vtx1), sizeof(vtx1));
    if (isLE == false)
    {
    uint32_t sectionEnd = base + vtx1.size;

    ConvertAttributeTable(in, out, base + vtx1.vertexFormatOffset, base + vtx1.posDataOffset);

    uint32_t colStart = sectionEnd;
    for (int i = 0; i < 2; ++i)
        if (vtx1.colDataOffset[i] != 0)
            colStart = std::min(colStart, base + vtx1.colDataOffset[i]);

    std::vector<uint32_t> vertexOffsets = {
        vtx1.posDataOffset, vtx1.nrmDataOffset, vtx1.nbtDataOffset,
        vtx1.texDataOffset[0], vtx1.texDataOffset[1], vtx1.texDataOffset[2],
        vtx1.texDataOffset[3], vtx1.texDataOffset[4], vtx1.texDataOffset[5],
        vtx1.texDataOffset[6], vtx1.texDataOffset[7]
    };
    ConvertVertexData(in, out, vertexOffsets, base, colStart);

CopyColorData(in, out, base, sectionEnd, vtx1.colDataOffset);

ConvertTexDataSections(in, out, vtx1, base, sectionEnd);
    }
    else
    {
    uint32_t sectionEnd = base + Swap32(vtx1.size);

    ConvertAttributeTable(in, out, base + Swap32(vtx1.vertexFormatOffset), base + Swap32(vtx1.posDataOffset));

    uint32_t colStart = sectionEnd;
    for (int i = 0; i < 2; ++i)
        if (Swap32(vtx1.colDataOffset[i]) != 0)
            colStart = std::min(colStart, base + Swap32(vtx1.colDataOffset[i]));

    std::vector<uint32_t> vertexOffsets = {
        Swap32(vtx1.posDataOffset), Swap32(vtx1.nrmDataOffset), Swap32(vtx1.nbtDataOffset),
        Swap32(vtx1.texDataOffset[0]), Swap32(vtx1.texDataOffset[1]), Swap32(vtx1.texDataOffset[2]),
        Swap32(vtx1.texDataOffset[3]), Swap32(vtx1.texDataOffset[4]), Swap32(vtx1.texDataOffset[5]),
        Swap32(vtx1.texDataOffset[6]), Swap32(vtx1.texDataOffset[7])
    };
    ConvertVertexData(in, out, vertexOffsets, base, colStart);

CopyColorDataLE(in, out, base, sectionEnd,vtx1.colDataOffset);

ConvertTexDataSectionsLE(in, out, vtx1, base, sectionEnd);
    }

}

void ConvertEVP1JointCountTable(std::ifstream& in, std::ofstream& out, uint32_t start, uint32_t stop) {
    for (uint32_t pos = start; pos < stop; pos += 2) {
        in.seekg(pos, std::ios::beg);
        uint16_t val;
        in.read(reinterpret_cast<char*>(&val), 2);
        uint16_t swapped = Swap16(val);
        out.seekp(pos, std::ios::beg);
        out.write(reinterpret_cast<char*>(&swapped), 2);
    }
}

void ConvertEVP1WeightTable(std::ifstream& in, std::ofstream& out, uint32_t start, uint32_t stop) {
    for (uint32_t pos = start; pos < stop; pos += 4) {
        in.seekg(pos, std::ios::beg);
        uint32_t val;
        in.read(reinterpret_cast<char*>(&val), 4);
        uint32_t swapped = Swap32(val);
        out.seekp(pos, std::ios::beg);
        out.write(reinterpret_cast<char*>(&swapped), 4);
    }
}
void CopyRawBlock(std::ifstream& in, std::ofstream& out, uint32_t offset, uint32_t endOffset) {
    const size_t bufferSize = 4096;
    char buffer[bufferSize];

    in.seekg(offset);
    out.seekp(offset);

    uint32_t remaining = endOffset - offset;
    while (remaining > 0) {
        size_t chunk = std::min(static_cast<uint32_t>(bufferSize), remaining);
        in.read(buffer, chunk);
        out.write(buffer, chunk);
        remaining -= chunk;
    }
}
void ConvertRaw16Block(std::ifstream& in, std::ofstream& out, uint32_t offset, uint32_t endOffset) {
    in.seekg(offset);
    out.seekp(offset);

    uint32_t count = (endOffset - offset) / 2;
    for (uint32_t i = 0; i < count; ++i) {
        uint16_t value;
        in.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
        value = Swap16(value);
        out.write(reinterpret_cast<char*>(&value), sizeof(uint16_t));
    }
}
void ConvertEVP1(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());
    EVP1Header header;
    in.read(reinterpret_cast<char*>(&header), sizeof(header));

    std::reverse(header.magic, header.magic + 4);
    header.size              = Swap32(header.size);
    header.matrixCount       = Swap16(header.matrixCount);
    header.padding           = Swap16(header.padding);
    header.jointCountOffset  = Swap32(header.jointCountOffset);
    header.indexTableOffset  = Swap32(header.indexTableOffset);
    header.weightTableOffset = Swap32(header.weightTableOffset);
    header.inverseBindOffset = Swap32(header.inverseBindOffset);
    out.write(reinterpret_cast<char*>(&header), sizeof(header));
    if(isLE==false)
    {
CopyRawBlock(in, out, base + header.jointCountOffset, base + header.indexTableOffset);

ConvertRaw16Block(in, out, base + header.indexTableOffset, header.weightTableOffset + base);

ConvertRaw32Block(in, out, header.weightTableOffset + base,header.inverseBindOffset + base);

for (uint16_t i = 0; i < header.matrixCount * 2 + 1; i++) {
    uint32_t offset = base + header.inverseBindOffset + i * sizeof(float) * 12;
    in.seekg(offset, std::ios::beg);
    uint32_t matrix[12];
    in.read(reinterpret_cast<char*>(matrix), sizeof(matrix));

    for (int j = 0; j < 12; ++j) {
        matrix[j] = Swap32(matrix[j]);
    }

    out.seekp(offset, std::ios::beg);
    out.write(reinterpret_cast<char*>(matrix), sizeof(matrix));
}
CopyRawBlock(in, out, in.tellg(),base + header.size);
    }
    else
    {
        CopyRawBlock(in, out, base + Swap32(header.jointCountOffset), base + Swap32(header.indexTableOffset));

ConvertRaw16Block(in, out, base + Swap32(header.indexTableOffset), Swap32(header.weightTableOffset) + base);

ConvertRaw32Block(in, out, Swap32(header.weightTableOffset) + base,Swap32(header.inverseBindOffset) + base);

for (uint16_t i = 0; i < Swap16(header.matrixCount) * 2 + 1; i++) {
    uint32_t offset = base + Swap32(header.inverseBindOffset) + i * sizeof(float) * 12;
    in.seekg(offset, std::ios::beg);
    uint32_t matrix[12];
    in.read(reinterpret_cast<char*>(matrix), sizeof(matrix));

    for (int j = 0; j < 12; ++j) {
        matrix[j] = Swap32(matrix[j]);
    }

    out.seekp(offset, std::ios::beg);
    out.write(reinterpret_cast<char*>(matrix), sizeof(matrix));
}
CopyRawBlock(in, out, in.tellg(),base + Swap32(header.size));
        
    }
}

void CopyDRW1DataArray(std::ifstream& in, std::ofstream& out, uint32_t start, uint32_t stop) {
    for (uint32_t pos = start; pos < stop; pos += 2) {
        in.seekg(pos, std::ios::beg);
        uint16_t val;
        in.read(reinterpret_cast<char*>(&val), 2);
        uint16_t swapped = Swap16(val);
        out.seekp(pos, std::ios::beg);
        out.write(reinterpret_cast<char*>(&swapped), 2);
    }
}



void ConvertDRW1(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());
DRW1Header header;
in.read(reinterpret_cast<char*>(&header), sizeof(header));

std::reverse(header.magic, header.magic + 4);
header.size                   = Swap32(header.size);
header.elementCount           = Swap16(header.elementCount);
header.padding                = Swap16(header.padding);
header.matrixTypeArrayOffset = Swap32(header.matrixTypeArrayOffset);
header.dataArrayOffset        = Swap32(header.dataArrayOffset);

out.write(reinterpret_cast<char*>(&header), sizeof(header));
if (isLE == false)
{
in.seekg(base + header.matrixTypeArrayOffset, std::ios::beg);
std::vector<char> types(header.elementCount);
in.read(types.data(), types.size());
out.seekp(base + header.matrixTypeArrayOffset, std::ios::beg);
out.write(types.data(), types.size());

CopyDRW1DataArray(in, out, base + header.dataArrayOffset, base + header.size);
}
else
{
    in.seekg(base + Swap32(header.matrixTypeArrayOffset), std::ios::beg);
std::vector<char> types(Swap16(header.elementCount));
in.read(types.data(), types.size());
out.seekp(base + Swap32(header.matrixTypeArrayOffset), std::ios::beg);
out.write(types.data(), types.size());

CopyDRW1DataArray(in, out, base + Swap32(header.dataArrayOffset), base + Swap32(header.size));
}
}

void ConvertJNT1JointData(std::ifstream& in, std::ofstream& out, uint32_t start, uint16_t jointCount) {
    for (uint16_t i = 0; i < jointCount; ++i) {
        uint32_t base = start + i * 0x40;

        in.seekg(base + 0x00); uint16_t flags; in.read((char*)&flags, 2);
        flags = Swap16(flags); out.seekp(base + 0x00); out.write((char*)&flags, 2);

in.seekg(base + 0x02);
char inheritFlag;
in.read(&inheritFlag, 1);
out.seekp(base + 0x02);
out.write(&inheritFlag, 1);

in.seekg(base + 0x03);
char padByte;
in.read(&padByte, 1);
out.seekp(base + 0x03);
out.write(&padByte, 1);

        for (int j = 0; j < 3; ++j) {
            uint32_t pos = base + 0x04 + j * 4;
            uint32_t f; in.seekg(pos); in.read((char*)&f, 4);
            f = Swap32(f); out.seekp(pos); out.write((char*)&f, 4);
        }

        for (int j = 0; j < 4; ++j) {
            uint32_t pos = base + 0x10 + j * 2;
            uint16_t s; in.seekg(pos); in.read((char*)&s, 2);
            s = Swap16(s); out.seekp(pos); out.write((char*)&s, 2);
        }

        for (int j = 0; j < 10; ++j) {
            uint32_t pos = base + 0x18 + j * 4;
            uint32_t f; in.seekg(pos); in.read((char*)&f, 4);
            f = Swap32(f); out.seekp(pos); out.write((char*)&f, 4);
        }
    }
}

void ConvertJNT1RemapTable(std::ifstream& in, std::ofstream& out, uint32_t start, uint16_t stop) {
    for (uint32_t pos = start; pos < stop; pos += 2) {
        in.seekg(pos, std::ios::beg);
        uint16_t val;
        in.read(reinterpret_cast<char*>(&val), 2);
        uint16_t swapped = Swap16(val);
        out.seekp(pos, std::ios::beg);
        out.write(reinterpret_cast<char*>(&swapped), 2);
    }
}

void CopyJNT1StringTable(std::ifstream& in, std::ofstream& out, uint32_t start, uint16_t stop) {
for (uint32_t pos = start; pos < stop; pos += 2) {
        in.seekg(pos, std::ios::beg);
        uint16_t val;
        in.read(reinterpret_cast<char*>(&val), 2);
        uint16_t swapped = val;
        out.seekp(pos, std::ios::beg);
        out.write(reinterpret_cast<char*>(&swapped), 2);
    }
}



void ConvertJNT1(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());
    JNT1Header header;
    in.read(reinterpret_cast<char*>(&header), sizeof(header));

    std::reverse(header.magic, header.magic + 4);
    header.size                  = Swap32(header.size);
    header.jointCount            = Swap16(header.jointCount);
    header.padding               = Swap16(header.padding);
    header.transformTableOffset = Swap32(header.transformTableOffset);
    header.remapTableOffset     = Swap32(header.remapTableOffset);
    header.nameTableOffset      = Swap32(header.nameTableOffset);

    out.write(reinterpret_cast<char*>(&header), sizeof(header));

    if (isLE == false)
    {
    ConvertJNT1JointData(in, out, base + header.transformTableOffset, header.jointCount);
    ConvertJNT1RemapTable(in, out, base + header.remapTableOffset, base + header.size); 
    in.seekg(base + header.nameTableOffset + 6, std::ios::beg);
    uint16_t offset;
    in.read(reinterpret_cast<char*>(&offset), 2);
    offset = Swap16(offset);
    uint32_t stringTableStart = base + header.nameTableOffset + offset;
    CopyJNT1StringTable(in, out, stringTableStart, base + header.size);
    }
    else
    {
        ConvertJNT1JointData(in, out, base + Swap32(header.transformTableOffset), Swap16(header.jointCount));
    ConvertJNT1RemapTable(in, out, base + Swap32(header.remapTableOffset), base + Swap32(header.size)); 
    in.seekg(base + Swap32(header.nameTableOffset) + 6, std::ios::beg);
    uint16_t offset;
    in.read(reinterpret_cast<char*>(&offset), 2);
    uint32_t stringTableStart = base + Swap32(header.nameTableOffset) + offset;
    CopyJNT1StringTable(in, out, stringTableStart, base + Swap32(header.size));
    }
}
void ConvertRemapTable(std::ifstream& in, std::ofstream& out, uint32_t offset, uint32_t endOffset) {
    uint32_t count = (endOffset - offset) / 2;
    in.seekg(offset);
    out.seekp(offset);

    for (uint32_t i = 0; i < count; ++i) {
        uint16_t index;
        in.read(reinterpret_cast<char*>(&index), sizeof(uint16_t));
        index = Swap16(index);
        out.write(reinterpret_cast<char*>(&index), sizeof(uint16_t));
    }
}

void ConvertShapeData(std::ifstream& in, std::ofstream& out, uint32_t offset, uint16_t shapeCount) {
    in.seekg(offset);
    out.seekp(offset);

    for (uint16_t i = 0; i < shapeCount; ++i) {
        ShapeData shape;
        in.read(reinterpret_cast<char*>(&shape), sizeof(ShapeData));

        shape.matrixGroupCount      = Swap16(shape.matrixGroupCount);
        shape.attributesOffset      = Swap16(shape.attributesOffset);
        shape.firstMatrixDataIndex  = Swap16(shape.firstMatrixDataIndex);
        shape.firstMatrixGroupIndex = Swap16(shape.firstMatrixGroupIndex);

        shape.boundingBoxMinX = Swap32(shape.boundingBoxMinX);
        shape.boundingBoxMinY = Swap32(shape.boundingBoxMinY);
        shape.boundingBoxMinZ = Swap32(shape.boundingBoxMinZ);
        shape.boundingBoxMaxX = Swap32(shape.boundingBoxMaxX);
        shape.boundingBoxMaxY = Swap32(shape.boundingBoxMaxY);
        shape.boundingBoxMaxZ = Swap32(shape.boundingBoxMaxZ);
        shape.boundingBoxMaxZ2 = Swap32(shape.boundingBoxMaxZ2);

        out.write(reinterpret_cast<char*>(&shape), sizeof(ShapeData));
    }
}

void ConvertMatrixData(std::ifstream& in, std::ofstream& out, uint32_t start, uint32_t stop) {
for (uint32_t pos = start; pos < stop; pos += 2) {
        MatrixData data;
        in.read(reinterpret_cast<char*>(&data), sizeof(MatrixData));

        data.useMtxIndex      = Swap16(data.useMtxIndex);
        data.useMtxCount      = Swap16(data.useMtxCount);
        data.firstUseMtxIndex = Swap32(data.firstUseMtxIndex);

        out.write(reinterpret_cast<char*>(&data), sizeof(MatrixData));
    }
}

void ConvertSHP1(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());

    SHP1Header header;
    in.read(reinterpret_cast<char*>(&header), sizeof(header));

    std::reverse(header.magic, header.magic + 4);
    header.chunkSize              = Swap32(header.chunkSize);
    header.sectionCount           = Swap16(header.sectionCount);
    header.padding                = Swap16(header.padding);
    header.shapeDataOffset        = Swap32(header.shapeDataOffset);
    header.remapTableOffset       = Swap32(header.remapTableOffset);
    header.nameTableOffset        = Swap32(header.nameTableOffset);
    header.attributeTableOffset   = Swap32(header.attributeTableOffset);
    header.matrixTableOffset      = Swap32(header.matrixTableOffset);
    header.primitiveDataOffset    = Swap32(header.primitiveDataOffset);
    header.matrixDataOffset       = Swap32(header.matrixDataOffset);
    header.matrixGroupTableOffset = Swap32(header.matrixGroupTableOffset);

    out.write(reinterpret_cast<char*>(&header), sizeof(header));
    if (isLE == false)
    {
    out.seekp(base + header.shapeDataOffset);
    ConvertShapeData(in, out, base + header.shapeDataOffset, header.sectionCount);

    out.seekp(base + header.remapTableOffset);
    ConvertRemapTable(in, out, base + header.remapTableOffset, base + header.attributeTableOffset);

    ConvertRaw32Block(in, out, base + header.attributeTableOffset, base + header.matrixTableOffset);
    ConvertRaw16Block(in, out, base + header.matrixTableOffset, base + header.primitiveDataOffset);
    CopyRawBlock(in, out, base + header.primitiveDataOffset, base + header.matrixDataOffset);
    ConvertMatrixData(in, out, base + header.matrixDataOffset, base + header.matrixGroupTableOffset);
    ConvertRaw32Block(in, out, base + header.matrixGroupTableOffset, base + header.chunkSize);
    }
    else
    {
    out.seekp(base + Swap32(header.shapeDataOffset));
    ConvertShapeData(in, out, base + Swap32(header.shapeDataOffset), Swap16(header.sectionCount));

    out.seekp(base + Swap32(header.remapTableOffset));
    ConvertRemapTable(in, out, base + Swap32(header.remapTableOffset), base + Swap32(header.attributeTableOffset));
    ConvertRaw32Block(in, out, base + Swap32(header.attributeTableOffset), base + Swap32(header.matrixTableOffset));
    ConvertRaw16Block(in, out, base + Swap32(header.matrixTableOffset), base + Swap32(header.primitiveDataOffset));
    CopyRawBlock(in, out, base + Swap32(header.primitiveDataOffset), base + Swap32(header.matrixDataOffset));
    ConvertMatrixData(in, out, base + Swap32(header.matrixDataOffset), base + Swap32(header.matrixGroupTableOffset));
    ConvertRaw32Block(in, out, base + Swap32(header.matrixGroupTableOffset), base + Swap32(header.chunkSize));
    }
}

void ConvertMaterialEntries(std::ifstream& in, std::ofstream& out, uint32_t offset, uint16_t count) {
    in.seekg(offset);
    out.seekp(offset);

    for (uint16_t i = 0; i < count; ++i) {
        uint8_t raw[0x14C];
        in.read(reinterpret_cast<char*>(raw), 0x14C);

        const uint32_t swapOffsets[] = {
            0x008, 0x00C, 0x014, 0x018, 0x028, 0x038, 0x048, 0x05C,
            0x084, 0x094, 0x0BC, 0x0DC, 0x0E4, 0x104, 0x124,
            0x144, 0x146, 0x148, 0x14A
        };

        const uint32_t swapCounts[] = {
            2, 4, 2, 8, 8, 8, 10, 20,
            8, 4, 16, 4, 16, 16, 16,
            1, 1, 1, 1
        };

        for (size_t j = 0; j < std::size(swapOffsets); ++j) {
            uint16_t* ptr = reinterpret_cast<uint16_t*>(&raw[swapOffsets[j]]);
            for (uint32_t k = 0; k < swapCounts[j]; ++k) {
                ptr[k] = Swap16(ptr[k]);
            }
        }

        out.write(reinterpret_cast<char*>(raw), 0x14C);
    }
}

void ConvertMaterialEntries2(std::ifstream& in, std::ofstream& out, uint32_t offset, uint16_t count) {
    in.seekg(offset);
    out.seekp(offset);

    for (uint16_t i = 0; i < count; ++i) {
        uint8_t raw[0x138];
        in.read(reinterpret_cast<char*>(raw), 0x138);

        const uint32_t swapOffsets[] = {
            0x014, 0x030, 0x4C, 0x68
        };

        const uint32_t swapCounts[] = {
            6, 6, 6, 6
        };

        for (size_t j = 0; j < std::size(swapOffsets); ++j) {
            uint32_t* ptr = reinterpret_cast<uint32_t*>(&raw[swapOffsets[j]]);
            for (uint32_t k = 0; k < swapCounts[j]; ++k) {
                ptr[k] = Swap32(ptr[k]);
            }
        }

        out.write(reinterpret_cast<char*>(raw), 0x138);
    }
}
void ConvertMaterialEntries4(std::ifstream& in, std::ofstream& out, uint32_t offset, uint16_t count) {
    in.seekg(offset);
    out.seekp(offset);

    for (uint16_t i = 0; i < count; ++i) {
        uint8_t raw[0x138];
        in.read(reinterpret_cast<char*>(raw), 0x8);

        const uint32_t swapOffsets[] = {
            0x00
        };

        const uint32_t swapCounts[] = {
            1
        };

        for (size_t j = 0; j < std::size(swapOffsets); ++j) {
            uint32_t* ptr = reinterpret_cast<uint32_t*>(&raw[swapOffsets[j]]);
            for (uint32_t k = 0; k < swapCounts[j]; ++k) {
                ptr[k] = Swap32(ptr[k]);
            }
        }

        out.write(reinterpret_cast<char*>(raw), 0x138);
    }
}

void ConvertMaterialEntries3(std::ifstream& in, std::ofstream& out, uint32_t start, uint32_t stop) {
for (uint32_t pos = start; pos < stop; pos += 0x64) {
        uint8_t raw[0x64];
        in.read(reinterpret_cast<char*>(raw), 0x64);

        const uint32_t swapOffsets[] = {
            0x04, 0x1C
        };

        const uint32_t swapCounts[] = {
            5, 18
        };

        for (size_t j = 0; j < std::size(swapOffsets); ++j) {
            uint32_t* ptr = reinterpret_cast<uint32_t*>(&raw[swapOffsets[j]]);
            for (uint32_t k = 0; k < swapCounts[j]; ++k) {
                ptr[k] = Swap32(ptr[k]);
            }
        }

        out.write(reinterpret_cast<char*>(raw), 0x64);
    }
}

void ConvertMAT3Header(MAT3Header& header) {
    header.sectionSize = Swap32(header.sectionSize);
    header.materialCount = Swap16(header.materialCount);
    std::reverse(header.magic, header.magic + 4);
    uint32_t* offsets = reinterpret_cast<uint32_t*>(&header.materialEntryOffset);
    for (int i = 0; i < 30; ++i) {
        offsets[i] = Swap32(offsets[i]);
    }
}

void ConvertMAT3(std::ifstream& in, std::ofstream& out) {
    
    uint32_t base = static_cast<uint32_t>(in.tellg());
MAT3Header header;
in.read(reinterpret_cast<char*>(&header), sizeof(header));
ConvertMAT3Header(header);
out.write(reinterpret_cast<char*>(&header), sizeof(header));
if (isLE == false)
{
    ConvertMaterialEntries(in, out, base + header.materialEntryOffset, header.materialCount);
    ConvertRaw16Block(in, out, base + header.remapTableOffset, base + header.stringTableOffset);
    in.seekg(base + header.stringTableOffset + 6, std::ios::beg);
    uint16_t offset;
    in.read(reinterpret_cast<char*>(&offset), 2);
    offset = Swap16(offset);
    uint32_t stringTableStart = base + header.stringTableOffset + offset;
    ConvertRaw16Block(in, out, base + header.stringTableOffset, stringTableStart);
    CopyRawBlock(in, out, stringTableStart, base +header.indirectInfoOffset);
    ConvertMaterialEntries2(in, out, base +header.indirectInfoOffset, header.materialCount);
    ConvertMaterialEntries4(in, out, base +header.cullModeOffset,header.materialCount);
    CopyRawBlock(in, out,base + header.materialColorOffset, base +header.texMatrixOffset);
    ConvertMaterialEntries3(in, out, base +header.texMatrixOffset,base + header.textureRemapTableOffset);
    ConvertRaw16Block(in, out,base + header.textureRemapTableOffset, base + header.tevOrderInfoOffset);
    CopyRawBlock(in, out,base + header.tevOrderInfoOffset, base + header.tevColorOffset);
    ConvertRaw16Block(in, out,base + header.tevColorOffset, base + header.numTevStagesOffset);
    CopyRawBlock(in, out,base + header.numTevStagesOffset, base + header.nbtScaleOffset + 4);
    ConvertRaw32Block(in, out,base + header.nbtScaleOffset + 4,base +header.sectionSize);
}
else
{
        ConvertMaterialEntries(in, out, base + Swap32(header.materialEntryOffset), Swap16(header.materialCount));
    ConvertRaw16Block(in, out, base + Swap32(header.remapTableOffset), base + Swap32(header.stringTableOffset));
    in.seekg(base + Swap32(header.stringTableOffset) + 6, std::ios::beg);
    uint16_t offset;
    
    in.read(reinterpret_cast<char*>(&offset), 2);
    uint32_t stringTableStart = base + Swap32(header.stringTableOffset) + offset;
    ConvertRaw16Block(in, out, base + Swap32(header.stringTableOffset), stringTableStart);
    CopyRawBlock(in, out, stringTableStart, base +Swap32(header.indirectInfoOffset));
    ConvertMaterialEntries2(in, out, base +Swap32(header.indirectInfoOffset), Swap16(header.materialCount));
    ConvertMaterialEntries4(in, out, base +Swap32(header.cullModeOffset),Swap16(header.materialCount));
    CopyRawBlock(in, out,base + Swap32(header.materialColorOffset), base +Swap32(header.texMatrixOffset));
    ConvertMaterialEntries3(in, out, base +Swap32(header.texMatrixOffset),base + Swap32(header.textureRemapTableOffset));
    ConvertRaw16Block(in, out,base + Swap32(header.textureRemapTableOffset), base + Swap32(header.tevOrderInfoOffset));
    CopyRawBlock(in, out,base + Swap32(header.tevOrderInfoOffset), base + Swap32(header.tevColorOffset));
    ConvertRaw16Block(in, out,base + Swap32(header.tevColorOffset), base + Swap32(header.numTevStagesOffset));
    CopyRawBlock(in, out,base + Swap32(header.numTevStagesOffset), base + Swap32(header.nbtScaleOffset) + 4);
    ConvertRaw32Block(in, out,base + Swap32(header.nbtScaleOffset) + 4,base +Swap32(header.sectionSize));
}
}

void ConvertMDL3Header(MDL3Header& header) {
    header.sectionSize = Swap32(header.sectionSize);
    header.entryCount  = Swap16(header.entryCount);
    std::reverse(header.magic, header.magic + 4);
    uint32_t* offsets = reinterpret_cast<uint32_t*>(&header.packetOffset);
    for (int i = 0; i < 6; ++i) {
        offsets[i] = Swap32(offsets[i]);
    }
}

void ConvertMDL3(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());
MDL3Header header;
in.read(reinterpret_cast<char*>(&header), sizeof(header));
ConvertMDL3Header(header);
out.write(reinterpret_cast<char*>(&header), sizeof(header));
if (isLE == false)
{
in.seekg(base + header.packetOffset, std::ios::beg);
    uint32_t offset;
    in.read(reinterpret_cast<char*>(&offset), 4);
    offset = Swap32(offset);
    in.seekg(base + header.packetOffset + offset, std::ios::beg);
ConvertRaw32Block(in, out, base + header.packetOffset,base + header.packetOffset + offset);
CopyRawBlock(in, out,base + header.packetOffset + offset, base + header.subPacketLocationOffset);
ConvertRaw16Block(in, out,base + header.subPacketLocationOffset,base + header.matrixIndexOffset);
ConvertRaw32Block(in, out,base + header.matrixIndexOffset, base + header.indexesOffset);
    uint8_t value;
in.seekg(base + header.stringTableOffset + 4);
in.read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
in.seekg(base + header.stringTableOffset + value);
if (value != 0x64)
{
ConvertRaw16Block(in, out,base + header.stringTableOffset,in.tellg());
CopyRawBlock(in, out,in.tellg(), base + header.sectionSize);
}
else
{
    CopyRawBlock(in, out,base + header.stringTableOffset, base + header.sectionSize);
}
}
else
{
    in.seekg(base + Swap32(header.packetOffset), std::ios::beg);
    uint32_t offset;
    in.read(reinterpret_cast<char*>(&offset), 4);
    in.seekg(base + Swap32(header.packetOffset) + offset, std::ios::beg);
ConvertRaw32Block(in, out, base + Swap32(header.packetOffset),base + Swap32(header.packetOffset) + offset);
CopyRawBlock(in, out,base + Swap32(header.packetOffset) + offset, base + Swap32(header.subPacketLocationOffset));
ConvertRaw16Block(in, out,base + Swap32(header.subPacketLocationOffset),base + Swap32(header.matrixIndexOffset));
ConvertRaw32Block(in, out,base + Swap32(header.matrixIndexOffset), base + Swap32(header.indexesOffset));
    CopyRawBlock(in, out,base + Swap32(header.stringTableOffset), base + Swap32(header.sectionSize));
}
}

void ConvertTexHeader(std::ifstream& in, std::ofstream& out, uint32_t offset, uint16_t count) {
    in.seekg(offset);
    out.seekp(offset);

    for (uint16_t i = 0; i < count; ++i) {
        TextureHeader data;
        in.read(reinterpret_cast<char*>(&data), sizeof(TextureHeader));

        data.width    = Swap16(data.width);
        data.height   = Swap16(data.height);
        data.lodBias  = Swap32(data.lodBias);
        data.unpacked = Swap32(data.unpacked);

        out.write(reinterpret_cast<char*>(&data), sizeof(TextureHeader));
    }
}

void ConvertTEX1(std::ifstream& in, std::ofstream& out) {
    uint32_t base = static_cast<uint32_t>(in.tellg());
TEX1Header header;
in.read(reinterpret_cast<char*>(&header), sizeof(header));
std::reverse(header.magic, header.magic + 4);
    header.sectionSize         = Swap32(header.sectionSize);
    header.textureCount        = Swap16(header.textureCount);
    header.textureHeaderOffset = Swap32(header.textureHeaderOffset);
    header.stringTableOffset   = Swap32(header.stringTableOffset);
out.write(reinterpret_cast<char*>(&header), sizeof(header));
if (isLE == false)
{
ConvertTexHeader(in, out, base +header.textureHeaderOffset,header.textureCount);
CopyRawBlock(in, out,in.tellg(), base + header.stringTableOffset);
in.seekg(base + header.stringTableOffset + 6, std::ios::beg);
    uint16_t offset;
    in.read(reinterpret_cast<char*>(&offset), 2);
    offset = Swap16(offset);
    uint32_t stringTableStart = base + header.stringTableOffset + offset;
    ConvertRaw16Block(in, out, base + header.stringTableOffset, stringTableStart);
    CopyRawBlock(in, out, stringTableStart, base +header.sectionSize);
}
else
{
    ConvertTexHeader(in, out, base +Swap32(header.textureHeaderOffset),Swap16(header.textureCount));
CopyRawBlock(in, out,in.tellg(), base + Swap32(header.stringTableOffset));
in.seekg(base + Swap32(header.stringTableOffset) + 6, std::ios::beg);
    uint16_t offset;
    in.read(reinterpret_cast<char*>(&offset), 2);
    uint32_t stringTableStart = base + Swap32(header.stringTableOffset) + offset;
    ConvertRaw16Block(in, out, base + Swap32(header.stringTableOffset), stringTableStart);
    CopyRawBlock(in, out, stringTableStart, base +Swap32(header.sectionSize));
}
}

int main(int argc, char* argv[]) {

    std::string inputPath  = argv[1];
    std::string  outputPath;
    if (!argv[2])
    {
outputPath = inputPath + "_out.bdl";
    }
    else
{
outputPath = argv[2];
}
if (argc < 2) {
        std::cerr << "Usage: bdlEndians.exe <input.bdl> (output.bdl)\n";
        return 1;
    }
    std::ifstream in(inputPath, std::ios::binary);
    std::ofstream out(outputPath, std::ios::binary);

    if (!in || !out) {
        std::cerr << "404 file not found.\n";
        return 1;
    }

    BDLHeader header;
    in.read(reinterpret_cast<char*>(&header), sizeof(header));
    ConvertHeaderEndian(header);
    out.write(reinterpret_cast<char*>(&header), sizeof(header));

    char padding[8];
    in.read(padding, 8);
    out.write(padding, 8);

    while (in.peek() != EOF) {
        char magic[4];
        in.read(magic, 4);
        in.seekg(-4, std::ios::cur);

        std::string magicStr(magic, 4);
        if (magicStr == "1FNI") {
            isLE = true;
            ConvertINF1(in, out);
        }
        else if (magicStr == "INF1") {
            ConvertINF1(in, out);
        }
        else if (magicStr == "VTX1" || magicStr == "1XTV") {
            ConvertVTX1(in, out);
        }
        else if (magicStr == "EVP1" || magicStr == "1PVE") {
    ConvertEVP1(in, out);
}
else if (magicStr == "DRW1" || magicStr == "1WRD") {
    ConvertDRW1(in, out);
}
else if (magicStr == "JNT1" || magicStr == "1TNJ") {
    ConvertJNT1(in, out);
}
else if (magicStr == "SHP1"|| magicStr == "1PHS") {
    ConvertSHP1(in, out);
}
else if (magicStr == "MAT3"|| magicStr == "3TAM") {
    ConvertMAT3(in, out);
}
else if (magicStr == "MDL3"|| magicStr == "3LDM") {
    ConvertMDL3(in, out);
}
else if (magicStr == "TEX1"|| magicStr == "1XET") {
    ConvertTEX1(in, out);
}
else {
            uint32_t sectionSize;
            in.read(magic, 4);
            in.read(reinterpret_cast<char*>(&sectionSize), 4);
            sectionSize = Swap32(sectionSize);
            in.seekg(sectionSize - 8, std::ios::cur);
        }
    }

    std::cout << "DONE\n";
    return 0;
}