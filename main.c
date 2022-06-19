/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:32:20 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/18 15:12:12 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int search(int* nums, int numsSize, int target){
    int start = 0, end = numsSize - 1, i = 0,med;
    while (start <= end)
    {
      med = (start + end) / 2;
       if (target == nums[med])
            return (med);
        else if (target > nums[med])
            start = med + 1;
        else
            end = med - 1;
    }
    if (start > end)
        return (-1);
    return (start);
}
int main()
{
    int a[] = {1, 3, 5, 7};
    printf("It Is : %d\n", search(a, 4, 13));
}