/* 
 * File:   split.h
 * Author: christian
 *
 * Created on 12. Mai 2014, 15:17
 */

#ifndef SPLIT_H
#define	SPLIT_H

struct split
{
  enum empties_t { empties_ok, no_empties };
};

template <typename Container>
Container& split(
  Container&                            result,
  const typename Container::value_type& s,
  const typename Container::value_type& delimiters)
{
  result.clear();
  size_t current;
  size_t next = -1;
  do
  {
    current = next + 1;
    next = s.find_first_of( delimiters, current );
    result.push_back( s.substr( current, next - current ) );
  }
  while (next != Container::value_type::npos);
  return result;
}



#endif	/* SPLIT_H */

