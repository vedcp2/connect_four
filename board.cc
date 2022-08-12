#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col > Board::kBoardWidth - 1 || col < 0) {
    throw std::runtime_error("invalid column");
  }
  int full_count = 0;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    } else {
      full_count++;
    }
  }
  if (full_count == Board::kBoardHeight) {
    throw std::runtime_error("column is filled");
  }
}

bool LeftDiagHelper(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = Board::kBoardWidth - 1; j > -1; j--) {
      int add_row = 1;
      int add_col = 1;
      if (b.board[i][j] == disk) {
        int count = 1;
        while (i + add_row < Board::kBoardHeight && j - add_col > -1) {
          if (b.board[i + add_row][j - add_col] == disk) {
            count++;
            add_row++;
            add_col++;
          } else
            break;
          if (count == 4) {
            return true;
          }
        }
      } else
        continue;
    }
  }
  return false;
}

bool RightDiagHelper(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      int add_row = 1;
      int add_col = 1;
      if (b.board[i][j] == disk) {
        int count = 1;
        while (i + add_row < Board::kBoardHeight &&
               j + add_col < Board::kBoardWidth) {
          if (b.board[i + add_row][j + add_col] == disk) {
            count++;
            add_row++;
            add_col++;
          } else
            break;
          if (count == 4) {
            return true;
          }
        }
      } else
        continue;
    }
  }
  return false;
}

bool VertHelper(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    int count = 0;
    for (int j = 0; j < Board::kBoardHeight; j++) {
      if (b.board[j][i] == disk) {
        count++;
      } else {
        count = 0;
      }
      if (count == 4) {
        return true;
      }
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    for (int i = 0; i < Board::kBoardHeight; i++) {
      int count = 0;
      for (int j = 0; j < Board::kBoardWidth; j++) {
        if (b.board[i][j] == disk) {
          count++;
        } else {
          count = 0;
        }
        if (count == 4) {
          return true;
        }
      }
    }
    return false;
  }
  if (to_check == WinningDirection::kVertical) {
    return VertHelper(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return LeftDiagHelper(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    return RightDiagHelper(b, disk);
  }
  return false;
}

bool CheckForWinner(Board& b, DiskType disk) {
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return ((row < Board::kBoardHeight && row >= 0) &&
          (col < Board::kBoardWidth && col >= 0));
}

std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}