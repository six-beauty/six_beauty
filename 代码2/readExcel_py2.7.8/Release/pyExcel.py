import os
import xlrd

def from_this_dir(filename):
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), filename)

class pyExcel():

    def __init__(self,fileName,index):
        self.book=xlrd.open_workbook(from_this_dir(str(fileName)))
        self.sheet=self.book.sheet_by_index(int(index))

    def getCell(self,rown,coln):
        try:
            cell=self.sheet.cell(rown,coln);
            result=cell.value
        except:
            return None
        if(cell.ctype==xlrd.book.XL_CELL_TEXT):
            return result.encode('utf-8')
        elif(cell.ctype==xlrd.book.XL_CELL_NUMBER):
            ft=float(result)
            return ft
        elif(cell.ctype==xlrd.book.XL_CELL_EMPTY):
            sz=str(' ')
            return sz

    def getRows(self):
        return self.sheet.nrows

    def getCols(self):
        return self.sheet.ncols

    def cellType(self,rown,coln):
        try:
            cell=self.sheet.cell(rown,coln)
        except:
            return None
        if(cell.ctype==xlrd.book.XL_CELL_NUMBER):
            return 0
        elif(cell.ctype==xlrd.book.XL_CELL_TEXT):
            return 1
    
