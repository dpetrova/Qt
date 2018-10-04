function Board(columnCount, rowCount, blockSize) {
    this.columnCount = columnCount;
    this.rowCount = rowCount;
    this.blockSize = blockSize;
    this.maxIndex = columnCount * rowCount;
    this.data = new Array(this.maxIndex);
}

//using prototype to add class methods

//initializes all array values to the null value
Board.prototype.init = function() {
    for (var i = 0; i < this.data.length; i++) {
        this.data[i] = null;
    }
}

//returns the array index from column/row coordinates
Board.prototype.index = function(column, row) {
    return column + (row * this.columnCount);
}

//assigns the data value on the board from column/row coordinates
Board.prototype.setData = function(data, column, row) {
    this.data[this.index(column, row)] = data;
}

//retrieves the data value in an array from column/row coordinates
Board.prototype.at = function(column, row) {
    return this.data[this.index(column, row)];
}
