#pragma once

#include "column.h"

namespace clickhouse {

/**
 * Represents various numeric columns.
 */
template <typename T>
class ColumnVector : public Column {
public:
    using DataType = T;

    ColumnVector();

    explicit ColumnVector(const std::vector<T>& data);

    /// Appends one element to the end of column.
    void Append(const T& value);

    /// Returns element at given row number.
    const T& At(size_t n) const;

    /// Returns element at given row number.
    const T& operator [] (size_t n) const;

public:
    /// Appends content of given column to the end of current one.
    void Append(ColumnRef column) override;

    /// Loads column data from input stream.
    bool Load(CodedInputStream* input, size_t rows) override;

    /// Saves column data to output stream.
    void Save(CodedOutputStream* output) override;

    /// Clear column data .
    void Clear() override;

    /// Returns count of rows in the column.
    size_t Size() const override;

    /// Makes slice of the current column.
    ColumnRef Slice(size_t begin, size_t len) override;

private:
    std::vector<T> data_;
};

using ColumnUInt8   = ColumnVector<uint8_t>;
using ColumnUInt16  = ColumnVector<uint16_t>;
using ColumnUInt32  = ColumnVector<uint32_t>;
using ColumnUInt64  = ColumnVector<uint64_t>;

using ColumnInt8    = ColumnVector<int8_t>;
using ColumnInt16   = ColumnVector<int16_t>;
using ColumnInt32   = ColumnVector<int32_t>;
using ColumnInt64   = ColumnVector<int64_t>;
using ColumnInt128  = ColumnVector<int128>;

using ColumnFloat32 = ColumnVector<float>;
using ColumnFloat64 = ColumnVector<double>;

}
