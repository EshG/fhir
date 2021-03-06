/*
 * Copyright 2018 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GOOGLE_FHIR_SEQEX_TEXT_TOKENIZER_H_
#define GOOGLE_FHIR_SEQEX_TEXT_TOKENIZER_H_

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "absl/strings/string_view.h"

namespace google {
namespace fhir {
namespace seqex {

class TextTokenizer {
 public:
  struct Token {
    std::string text;
    int char_start;
    int char_end;

    bool operator==(const Token& rhs) const {
      return std::tie(text, char_start, char_end) ==
             std::tie(rhs.text, rhs.char_start, rhs.char_end);
    }

    std::ostream& operator<<(std::ostream& os) const {
      os << text;
      return os;
    }
  };

  virtual ~TextTokenizer() {}

  // Creates a text tokenizer as specified by flags.
  static std::shared_ptr<TextTokenizer> FromFlags();

  // Decompose a text string into tokens.
  virtual std::vector<Token> Tokenize(absl::string_view text) const = 0;

 protected:
  // Apply additional processing to a set of tokens, generating a new set. This
  // processing might include steps like replacing numbers by a single numeric
  // token, adding bigrams or trigrams, and more, depending on flag settings.
  virtual std::vector<Token> ProcessTokens(
      const std::vector<Token>& tokens) const;

  // Replace numeric tokens in the provided vector with the default numeric
  // token string, retaining the character positions.
  void ReplaceNumbers(std::vector<Token>* tokens) const;

  std::vector<Token> GenerateBigrams(const std::vector<Token>& tokens) const;
  std::vector<Token> GenerateTrigrams(const std::vector<Token>& tokens) const;
};

// Breaks up text based on white-space and ignores punctuation. Applies
// replacement of numeric tokens, and adds bigrams and trigrams, if specified
// by flags.
class SimpleWordTokenizer : public TextTokenizer {
 public:
  std::vector<Token> Tokenize(absl::string_view text) const override;
};

// The text IS the token.
class SingleTokenTokenizer : public TextTokenizer {
 public:
  std::vector<Token> Tokenize(absl::string_view text) const override;
};

}  // namespace seqex
}  // namespace fhir
}  // namespace google

#endif  // GOOGLE_FHIR_SEQEX_TEXT_TOKENIZER_H_
